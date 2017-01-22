#include "io/ata.h"
#include "io/port.h"
#include "io/pci.h"
#include "mm/kmem.h"
#include "util/string.h"
#include "util/log.h"

static uint16_t identBuf[ATAIdentLength];

ata_device_t *ataList = NULL;

static ata_device_t *ataDetectDevice(ata_channel_t *channel, uint8_t type) {
    klog("detect ata device");

    ataSelect(channel, type);

    outb(ATARegCommand(channel), ATACmdIdent);
    uint8_t status = inb(ATARegStatus(channel));
    if (!status) return NULL;

    status = ataPoll(channel, ATAStatusERR | ATAStatusDRQ);

    if (status & ATAStatusERR) {
        uint16_t cc = inw(ATARegLBA1(channel));
        cc |= inb(ATARegLBA2(channel)) << 16;
        if (cc != ATAPIMagic1 && cc != ATAPIMagic2) return NULL;

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

    klog(ATAIdentATAPI(dev) ? "found atapi device" : "found ata device");

    return dev;
}

inline static uint32_t ataAddress(uint32_t bar, uint32_t def) {
    bar &= -4;
    return bar ? bar : def;
}

static void ataDetectChannel(uint32_t *bar, uint32_t def1, uint32_t def2) {
    klog("detect channel");

    ata_channel_t *channel = kalloc(KmemATAChannel);
    channel -> base     = ataAddress(bar[0], def1);
    channel -> control  = ataAddress(bar[1], def2);
    channel -> bmide    = 0;
    channel -> selected = 0;

    ata_device_t *master = ataDetectDevice(channel, ATADriveMaster);
    ata_device_t *slave  = ataDetectDevice(channel, ATADriveSlave);

    if (!master && !slave) kfree(KmemATAChannel, channel);
}

void initATA() {
    klog("init ata");

    kmemInitCache(KmemATAChannel, sizeof(ata_channel_t), NULL);
    kmemInitCache(KmemATADevice, sizeof(ata_device_t), NULL);

    pci_info_t *pci;
    for (pci = pciList; pci; pci = pci -> next) {
        if (pci -> class == PCIStorage && pci -> subclass == PCIIDE) {
            klog("detect ide device");

            ataDetectChannel(pci -> bar, ATAPrimaryBase, ATAPrimaryControl);
            ataDetectChannel(pci -> bar + 2, ATASecondaryBase, ATASecondaryControl);
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
    for (;;) {
        uint8_t status = inb(ATARegStatus(channel));
        if (!(status & ATAStatusBSY) && (!mask || (status & mask))) return status;
    }
}
