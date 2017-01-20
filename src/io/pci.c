#include "io/pci.h"
#include "io/port.h"

pci_info_t *pciList = NULL;

uint32_t pciConfigReadLong(uint8_t bus, uint8_t slot,
                           uint8_t func, uint8_t offset) {
    uint32_t addr;

    addr    =   PCIAddrPres;
    addr   |= ((uint32_t)bus)       << 16;
    addr   |= ((uint32_t)slot)    << 11;
    addr   |= ((uint32_t)func)      << 8;

    outl(PCIConfigAddr, addr);
    return inl(PCIConfigData);
}

void pciCheckBus(uint8_t bus) {
    uint8_t slot;
    for (slot = 0; slot < PCISlotLength; ++slot) {
        pciCheckDevice(bus, slot);
    }
}

static void appendPCIList(pci_info_t *device) {
    device -> next = pciList;
    pciList = device;
}

pci_info_t *pciCheckFunction(uint8_t bus, uint8_t slot, uint8_t func) {
    pci_info_t *device;
    uint32_t temp = pciConfigReadLong(bus, slot, func, 0);
    if ((temp & 0xffff) == PCINull) return NULL;

    device = kalloc(KmemPCI);
    appendPCIList(device);
    device -> bus = bus;
    device -> slot = slot;
    device -> func = func;

    uint32_t *base = (uint32_t *)&device -> vendorID;
    int i;
    base[0] = temp;
    for (i = 1; i < PCIInfoSize; ++i) {
        base[i] = pciConfigReadLong(bus, slot, func, i * 4);
    }

    return device;
}

void pciCheckDevice(uint8_t bus, uint8_t slot) {
    uint8_t func = 0;
    pci_info_t *device;

    device = pciCheckFunction(bus, slot, func);

    if (device -> headerType & PCIHeaderMF) {
        for (++func; func < PCIFuncLength; ++func) {
            pciCheckFunction(bus, slot, func);
        }
    }
}
