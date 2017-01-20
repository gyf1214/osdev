#ifndef __PCI
#define __PCI

#include "util/type.h"

#define PCIConfigAddr   0xcf8
#define PCIConfigData   0xcfc
#define PCISlotLength   32
#define PCIFuncLength   8

#define PCIAddrPres     (1 << 31)

#define PCIHeaderMF     (1 << 7)
#define PCINull         0xffff

#define PCIInfoSize     9

typedef struct pci_info {
    uint8_t bus, slot, func;
    uint16_t vendorID, deviceID;
    uint16_t command, status;
    uint8_t class, subclass, progIF, revisionID;
    uint8_t bist, headerType, latency, cacheLine;
    uint32_t bar[PCIBarLength];
    struct pci_info *next;
} pci_info_t;

extern pci_info_t *pciList;

uint32_t pciConfigReadLong(uint8_t bus, uint8_t slot,
                           uint8_t func, uint8_t offset);
void pciCheckBus(uint8_t bus);
void pciCheckDevice(uint8_t bus, uint8_t slot);
pci_info_t *pciCheckFunction(uint8_t bus, uint8_t slot, uint8_t func);
void pciCheckAll(void);
void initPCI(void);

#endif
