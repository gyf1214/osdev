#ifndef __ATA
#define __ATA

#include "util/type.h"

#define ATAPrimaryBase      0x1f0
#define ATAPrimaryControl   0x3f4
#define ATASecondaryBase    0x170
#define ATASecondaryControl 0x374

#define ATARegData(x)       ((x) -> base + 0)
#define ATARegError(x)      ((x) -> base + 1)
#define ATARegFeature(x)    ((x) -> base + 1)
#define ATARegSector(x)     ((x) -> base + 2)
#define ATARegLBA0(x)       ((x) -> base + 3)
#define ATARegLBA1(x)       ((x) -> base + 4)
#define ATARegLBA2(x)       ((x) -> base + 5)
#define ATARegDrive(x)      ((x) -> base + 6)
#define ATARegCommand(x)    ((x) -> base + 7)
#define ATARegStatus(x)     ((x) -> base + 7)
#define ATARegAltStatus(x)  ((x) -> ctrl + 2)
#define ATARegControl(x)    ((x) -> ctrl + 2)

#define ATAStatusERR        0x01
#define ATAStatusDRQ        0x08
#define ATAStatusDF         0x20
#define ATAStatusBSY        0x80

#define ATACmdIdent         0xec
#define ATACmdIdentPacket   0xa1
#define ATACmdRead          0x20

#define ATADriveMaster      0xa0
#define ATADriveSlave       0xb0

#define ATAControlHOB       0x80

#define ATAPIMagic1         0xeb14
#define ATAPIMagic2         0x9669
#define ATAPIMagic          ATAPIMagic1

#define ATADelay            4

#define ATAIdentSign        0
#define ATAIdentCapa        49
#define ATAIdentCmdSet      82
#define ATAIdentSize        60
#define ATAIdentSizeExt     100
#define ATAIdentModel       27

#define ATAIdentATAPI(x)    (((x) -> sign) & (1 << 15))
#define ATAIdentLBA(x)      (((x) -> capabilities) & (1 << 9))
#define ATAIdentLBA48(x)    (((x) -> commandSets) & (1 << 26))

#define ATADeviceLength     4
#define ATAModelLength      40
#define ATAIdentLength      256
#define ATAPollTry          10240

typedef struct ata_channel {
    uint16_t base, control;
    uint8_t selected;
}ata_channel_t;

typedef struct ata_device {
    ata_channel_t *channel;
    uint8_t type;
    uint16_t sign;
    uint32_t capabilities, commandSets;
    uint64_t size;
    char model[ATAModelLength + 1];
    struct ata_device *next;
}ata_device_t;

extern ata_device_t *ataList;

void initATA(void);
int ataSelect(ata_channel_t *channel, uint8_t type);
int ataPoll(ata_channel_t *channel, uint8_t mask);

#endif
