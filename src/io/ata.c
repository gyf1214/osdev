#include "io/ata.h"
#include "io/port.h"
#include "io/pci.h"
#include "mm/kmem.h"
#include "irq/pic.h"
#include "util/string.h"
#include "util/log.h"

static uint16_t identBuf[ATAIdentLength];
ata_device_t *ataDevices[ATADeviceLength];
static int ataCount;

static ata_device_t *ataDetectDevice(ata_channel_t *channel, uint8_t type) {
    if (!ataSelect(channel, type)) return NULL;

    outb(ATARegCommand(channel), ATACmdIdent);
    uint8_t status = inb(ATARegStatus(channel));
    if (!status) return NULL;

    status = ataPoll(channel, ATAStatusERR | ATAStatusDRQ);

    if (status & ATAStatusERR) {
        uint16_t cc = inb(ATARegLBA1(channel));
        cc |= inb(ATARegLBA2(channel)) << 8;
        if (cc != ATAPIMagic) return NULL;

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
    dev -> irq          = 0;

    int k;
    for (k = 0; k < ATAModelLength / 2; ++k) {
        dev -> model[2 * k] = (identBuf[k + ATAIdentModel] >> 8) & 0xff;
        dev -> model[2 * k + 1] = identBuf[k + ATAIdentModel] & 0xff;
    }
    dev -> model[ATAModelLength] = 0;

    if (ATAIdentLBA48(dev)) {
        dev -> size = *((uint64_t *)(identBuf + ATAIdentSizeExt));
    } else {
        dev -> size = *((uint32_t *)(identBuf + ATAIdentSize));
    }

    klog(ATAIdentATAPI(dev) ? "found atapi device" : "found ata device");
    klog(dev -> model);

    return dev;
}

inline static uint32_t ataAddress(uint32_t bar, uint32_t def) {
    bar &= -4;
    return bar ? bar : def;
}

static ata_channel_t *ataDetectChannel(uint32_t *bar, uint32_t def1, uint32_t def2) {
    ata_channel_t *channel = kalloc(KmemATAChannel);
    channel -> base     = ataAddress(bar[0], def1);
    channel -> control  = ataAddress(bar[1], def2);
    channel -> selected = 0;

    klog("detect ide master");
    ata_device_t *master = ataDetectDevice(channel, ATADriveMaster);
    ataDevices[ataCount++] = master;

    klog("detect ide slave");
    ata_device_t *slave  = ataDetectDevice(channel, ATADriveSlave);
    ataDevices[ataCount++] = slave;

    if (!master && !slave) {
        kfree(KmemATAChannel, channel);
        return NULL;
    } else {
        return channel;
    }
}

void initATA() {
    klog("init ata");

    kmemInitCache(KmemATAChannel, sizeof(ata_channel_t), NULL);
    kmemInitCache(KmemATADevice, sizeof(ata_device_t), NULL);

    pci_info_t *pci;
    ata_channel_t *channel;
    ataCount = 0;
    for (pci = pciList; pci; pci = pci -> next) {
        if (pci -> class == PCIStorage && pci -> subclass == PCIIDE) {
            klog("detect ide primary");
            channel = ataDetectChannel(pci -> bar, ATAPrimaryBase, ATAPrimaryControl);
            if (channel) channel -> irq = ATAPrimaryIRQ;
            picSetMask(channel -> irq, 0);

            klog("detect ide secondary");
            channel = ataDetectChannel(pci -> bar + 2, ATASecondaryBase, ATASecondaryControl);
            if (channel) channel -> irq = ATASecondaryIRQ;
            picSetMask(channel -> irq, 0);

            break;
        }
    }
}

int ataSelect(ata_channel_t *channel, uint8_t type) {
    if (channel -> selected == type) return 1;

    outb(ATARegDrive(channel), type);
    int i;
    for (i = 0; i < ATADelay; ++i) {
        inb(ATARegStatus(channel));
    }

    uint8_t status = ataPoll(channel, 0);
    channel -> selected = type;
    return !(status & ATAStatusBSY);
}

int ataPoll(ata_channel_t *channel, uint8_t mask) {
    int i;
    uint8_t status;
    for (i = 0; i < ATAPollTry; ++i) {
        status = inb(ATARegStatus(channel));
        if (!(status & ATAStatusBSY) && (!mask || (status & mask))) return status;
    }
    klog("ide device hang!!!!");
    return status;
}

void ataIRQHandler(int_frame_t frame) {
    klog("ata irq!");

    int irq = picIRQ(frame.intCode);
    if (irq < 0) return;
    int i;
    ata_device_t *dev;
    for (i = 0; i < ATADeviceLength; ++i) {
        dev = ataDevices[i];
        if (dev && dev -> channel -> selected == dev -> type
                && dev -> channel -> irq == irq) {
            dev -> irq = 1;
            break;
        }
    }
    picEOI(irq);
}

void ataWaitIRQ(ata_device_t *dev) {
    while (!dev -> irq);
    dev -> irq = 0;
}

int atapiRead(ata_device_t *dev, void *buf, uint32_t lba, uint8_t count) {
    static uint8_t packet[ATAPIPacketLength];
    ata_channel_t *channel = dev -> channel;

    memset(packet, 0, ATAPIPacketLength * sizeof(uint8_t));
    packet[0] = ATAPICmdRead;
    packet[2] = (lba >> 24) & 0xff;
    packet[3] = (lba >> 16) & 0xff;
    packet[4] = (lba >>  8) & 0xff;
    packet[5] = (lba      ) & 0xff;
    packet[9] = count;

    dev -> irq = 0;
    if (!ataSelect(channel, dev -> type)) return 0;
    outb(ATARegFeature(channel), 0);
    outb(ATARegLBA1(channel), ATAPISectorSize & 0xff);
    outb(ATARegLBA2(channel), ATAPISectorSize >> 8);
    outb(ATARegCommand(channel), ATACmdPacket);

    uint8_t status = ataPoll(channel, ATAStatusDRQ | ATAStatusERR);
    if (status & ATAStatusERR) return 0;

    outsw(ATARegData(channel), (uint16_t *)packet, ATAPIPacketLength / 2);
    int i;
    uint16_t *input = (uint16_t *)buf;
    for (i = 0; i < count; ++i) {
        ataWaitIRQ(dev);
        if (ataPoll(channel, ATAStatusDRQ | ATAStatusERR) & ATAStatusERR) {
            return 0;
        }
        insw(ATARegData(channel), input, ATAPISectorSize / 2);
        input += ATAPISectorSize / 2;
    }

    ataWaitIRQ(dev);
    ataPoll(channel, 0);

    return 1;
}
