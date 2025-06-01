#include <sys/types.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "hexioctrl.h"
#include "(PCI_DEVS)pci_codes.h"
#include <conio.h>

#define CONFIG_ADDRESS 0x0CF8	    // для записи адреса регистра, по которому будет доступ производиться
#define CONFIG_DATA 0x0CFC          // чтение/запись по указанному адресу

unsigned long genAddr(unsigned long bus, unsigned long device, unsigned long function, unsigned long offset) {
    return (1 << 31) | 
           ((bus & 0xFF) << 16) | 
           ((device & 0x1F) << 11) | 
           ((function & 0x07) << 8) | 
           (offset & 0xFC);
}

void printDeviceInfo(unsigned long venId, unsigned long devId, const std::string& deviceName, int deviceCount) {
	std::cout << "|---|-------|-------|----------------------------------------------------|" << std::endl;
    std::cout << "| " << std::setw(2) << deviceCount 
              << "| " << std::setw(6) << std::hex << std::uppercase << venId
              << "| " << std::setw(6) << devId
              << "| " << std::setw(51) << std::left << deviceName
              << "|" << std::endl;
}

void enumeratePCIDevices() {
    int deviceCount = 1;

    std::cout << "--------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(4) << "| #" 
              << std::setw(8) << "| VenID" 
              << std::setw(8) << "| DevID" << "| " 
              << std::setw(20) << "" << std::setw(31)<< "Device Name" << "|" << std::endl;

    for (int bus = 0; bus < 128; bus++) {
        for (int device = 0; device < 32; device++) {
            for (int function = 0; function < 8; function++) {

                _outpd(CONFIG_ADDRESS, genAddr(bus, device, function, 0x00));

                unsigned long val = _inpd(CONFIG_DATA);

                if (val == 0 || val == -1) continue;

                unsigned long devId = val >> 16;
                unsigned long venId = val & 0xFFFF;

                for (int i = 0; i < PCI_DEVTABLE_LEN; i++) {
                    if (PciDevTable[i].DevId == devId && 
                        PciDevTable[i].VenId == venId) {

                        printDeviceInfo(venId, devId, PciDevTable[i].ChipDesc, deviceCount++);

                        break;
                    }
                }
            }
        }
    }
	std::cout << "--------------------------------------------------------------------------" << std::endl;
}

int main() {
    ALLOW_IO_OPERATIONS;

    enumeratePCIDevices();

    std::cin.get();
    return 0;
}