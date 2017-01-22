#include "io/ata.h"
#include "io/port.h"
#include "io/pci.h"
#include "mm/kmem.h"

static uint16_t identBuf[ATAIdentLength];

ata_device_t *ataList = NULL;

static ata_device_t *ataDetectDevice(ata_channel_t *channel, uint8_t type) {
    ataSelect(channel, type);

    outb(ATARegCommand(channel), ATACmdIdent);
    if (!inb(ATARegStatus(channel))) return NULL;

    uint8_t status = ataPoll(channel, ATAStatusERR | ATAStatusDRQ);
    int atapi = 0;

    if (status & ATAStatusERR) {
        uint16_t cc = inb(ATARegLBA1(channel));
        cc |= inb(ATARegLBA2(channel)) << 16;
        if (cc != ATAPIMagic1 && cc != ATAPIMagic2) return NULL;

        atapi = 1;
        outb(ATARegCommand(channel), ATACmdIdentPacket);
        ataPoll(channel, ATAStatusDRQ);
    }

    insw(ATARegData(channel), identBuf, ATAIdentLength);

    ata_device_t *dev   = (ata_device_t *)kalloc(KmemATADevice);
    dev -> channel      = channel;
    dev -> type         = type;
    dev -> sign         = identBuf[ATAIdentSign];
    dev -> capabilities = *((uint32_t *)(identBuf + ATAIdentCapa));
    dev -> commandSets  = *((uint32_t *)(identBuf + ATAIdentCmdSet));
    dev -> next         = ataList;
    ataList             = dev;

    memcpy(dev -> model, identBuf + ATAIdentModel, ATAModelLength);
    dev -> model[ATAModelLength] = 0;

    if (ATAIdentLBA48(dev)) {
        dev -> size = *((uint64_t *)(identBuf + ATAIdentSizeExt));
    } else {
        dev -> size = *((uint32_t *)(identBuf + ATAIdentSize));
    }

    return dev;
}

inline static uint32_t ataAddress(uint32_t bar, uint32_t def) {
    bar &= -4;
    return bar ? bar : def;
}

static void ataDetectChannel(uint32_t *bar, uint32_t def1, uint32_t def2) {
    ata_channel_t *channel = kalloc(KmemATAChannel);
    channel -> base     = ataAddress(bar[0], def1);
    channel -> control  = ataAddress(bar[1], def2);
    channel -> bmide    = 0;
    channel -> selected = 0;

    ata_device_t *master = ataDetectDevice(channel, ATADriveMaster);
    ata_device_t *slave  = ataDetectDevice(channel, ATADriveSlave);

    if (!master && !slave) kfree(KmemATAChannel, channel);
}

static void ataDetectAll(uint32_t *bar) {
    memset(ataDeviceBuf, 0, ATADeviceLength * sizeof(ata_device_t *));
    ataDeviceCount = 0;

    ataDetectChannel(bar    , ATAPrimaryBase, ATAPrimaryControl);
    ataDetectChannel(bar + 2, ATASecondaryBase, ATASecondaryControl);
}

void initATA() {
    kmemInitCache(KmemATAChannel, sizeof(ata_channel_t), NULL);
    kmemInitCache(KmemATADevice, sizeof(ata_device_t), NULL);

    pci_info_t *pci;
    for (pci = pciList; pci; pci = pci -> next) {
        if (pci -> class == PCIStorage && pci -> subclass == PCIIDE) {
            ataDetectAll(pci -> bar);
        }
    }
}

void ataSelect(ata_channel_t *channel, uint8_t type) {
    if (channel -> selected == type) return;

    outb(ATARegDrive(channel), type);
    int i;
    for (i = 0; i < ATADelay; ++i) {
        inb(ATARegStatus(channel));
    }

    ataPoll(channel, 0);
}

int ataPoll(ata_channel_t *channel, uint8_t mask) {
    if (!mask) mask = 0xff;
    for (;;) {
        status = inb(ATARegStatus(channel));
        if (!(status & ATAStatusBSY) && (status & mask)) return status;
    }
}
