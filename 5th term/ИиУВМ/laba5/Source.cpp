#include <Windows.h>
#include <Setupapi.h>
#include <iostream>
#include <Cfgmgr32.h>
#include <vector>
#include <string>
#include <dbt.h>
#include <initguid.h>
#include <Usbiodef.h>
#include <conio.h>
#pragma comment(lib, "setupapi.lib")

using namespace std;

bool exitFlag = false;

struct USBDevice {
    wstring hardwareId;
    wstring deviceName;
    wstring devicePath;
    wstring productId;

    DEVINST devInstance;
    HDEVNOTIFY notifyHandle;

    bool isEjectable;
    bool isSafeRemovalInitiated = false;

    USBDevice(PDEV_BROADCAST_DEVICEINTERFACE deviceInfo, HWND hwnd = nullptr);
    USBDevice(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA deviceInfoData, HWND hwnd);
    USBDevice(const USBDevice& other);

    void registerForNotifications(HWND hwnd);
    void unregisterNotification() const;
    void ejectDevice() const;
    void displayDeviceInfo() const;
    static void removeDevice(const USBDevice& device);

    bool operator==(const USBDevice& other) const { return this->productId == other.productId; }
};

vector<USBDevice> devicesList;

USBDevice::USBDevice(PDEV_BROADCAST_DEVICEINTERFACE deviceInfo, HWND hwnd) {
    HDEVINFO deviceInfoSet = SetupDiCreateDeviceInfoList(nullptr, nullptr);
    SetupDiOpenDeviceInterfaceW(deviceInfoSet, deviceInfo->dbcc_name, NULL, nullptr);
    SP_DEVINFO_DATA deviceInfoData = {};
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    SetupDiEnumDeviceInfo(deviceInfoSet, 0, &deviceInfoData);
    *this = USBDevice(deviceInfoSet, deviceInfoData, hwnd);
}

USBDevice::USBDevice(HDEVINFO deviceInfoSet, SP_DEVINFO_DATA deviceInfoData, HWND hwnd) {
    devInstance = deviceInfoData.DevInst;
    TCHAR buffer[256] = {};

    SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, nullptr, (BYTE*)buffer, sizeof(buffer), nullptr);
    deviceName = buffer;

    SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_HARDWAREID, nullptr, (BYTE*)buffer, sizeof(buffer), nullptr);
    hardwareId = buffer;

    if (!hardwareId.empty() && hardwareId.find(L"PID_") != wstring::npos) {
        productId = hardwareId.substr(hardwareId.find(L"PID_") + 4, 4);
    }

    DWORD capabilities = 0;
    SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_CAPABILITIES, nullptr, (BYTE*)&capabilities, sizeof(capabilities), nullptr);
    isEjectable = capabilities & CM_DEVCAP_REMOVABLE;

    if (hwnd ) {
        SP_DEVICE_INTERFACE_DATA interfaceData = {};
        interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        SetupDiEnumDeviceInterfaces(deviceInfoSet, &deviceInfoData, &GUID_DEVINTERFACE_USB_DEVICE, 0, &interfaceData);

        DWORD requiredSize = 0;
        SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &interfaceData, nullptr, 0, &requiredSize, nullptr);

        PSP_INTERFACE_DEVICE_DETAIL_DATA detailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(requiredSize);
        detailData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
        SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &interfaceData, detailData, requiredSize, nullptr, &deviceInfoData);

        devicePath = detailData->DevicePath;
        free(detailData);

        registerForNotifications(hwnd);
    }
}

USBDevice::USBDevice(const USBDevice& other)
    : hardwareId(other.hardwareId), deviceName(other.deviceName), devicePath(other.devicePath),
    productId(other.productId), isEjectable(other.isEjectable), devInstance(other.devInstance),
    notifyHandle(other.notifyHandle) {}

void USBDevice::registerForNotifications(HWND hwnd) {
    DEV_BROADCAST_HANDLE filter = {};
    HANDLE deviceHandle = CreateFile(devicePath.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    filter.dbch_size = sizeof(filter);
    filter.dbch_devicetype = DBT_DEVTYP_HANDLE;
    filter.dbch_handle = deviceHandle;
    notifyHandle = RegisterDeviceNotification(hwnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE);
    CloseHandle(deviceHandle);
}

void USBDevice::unregisterNotification() const {
    UnregisterDeviceNotification(notifyHandle);
}

void USBDevice::removeDevice(const USBDevice& device) {
    for (size_t i = 0; i < devicesList.size(); ++i) {
        if (device == devicesList[i]) {
            devicesList[i].unregisterNotification();
            devicesList.erase(devicesList.begin() + i);
            break;
        }
    }
}

void showMenu() {
    cout << "Введите номер устройства чтобы его извлечь, или введите '0' для выхода\n";
    cout << "\nUSB устройства:\n\n";
}
void listDevices() {
    for (size_t i = 0; i < devicesList.size(); ++i) {
        cout << i + 1 << ". ";
        devicesList[i].displayDeviceInfo();
    }
}

void USBDevice::displayDeviceInfo() const {
    wcout << L"Название: " << deviceName << L"\n"
        << L"Hardware ID: " << hardwareId << L"\n"
        << L"Извлекаемое: " << (isEjectable ? L"Да" : L"Нет") << L"\n\n";
}

void USBDevice::ejectDevice() const {
    CM_Request_Device_Eject(devInstance, nullptr, nullptr, 0, 0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DEVICECHANGE) {

        switch (wParam) {
        case DBT_DEVICEARRIVAL: {
            auto* deviceInfo = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;

            if (deviceInfo->dbcc_classguid != GUID_DEVINTERFACE_USB_DEVICE) 
                break;

            USBDevice newDevice(deviceInfo, hwnd);

            if (newDevice.deviceName.empty())
                break;

            devicesList.push_back(newDevice);

            system("cls");
            cout << "Подключено: \n\033[38;5;141m";
            newDevice.displayDeviceInfo();
            cout << "\033[0m";
            showMenu();
            listDevices();
            break;
        }

        case DBT_DEVICEREMOVECOMPLETE: {
            USBDevice removedDevice((PDEV_BROADCAST_DEVICEINTERFACE)lParam);
            auto it = find(devicesList.begin(), devicesList.end(), removedDevice);
            if (it != devicesList.end()) {
                system("cls");
                if (it->isSafeRemovalInitiated) {
                    cout << "Извлечено безопасно: \n\033[38;5;119m";
                    it->displayDeviceInfo();
                    cout << "\033[0m";
                }
                else {
                    cout << "Извлечено небезопасно: \n\033[38;5;196m";
                    it->displayDeviceInfo();
                    cout << "\033[0m";
                }
                USBDevice::removeDevice(*it);
                showMenu();
                listDevices();
            }
            break;
        }

        case DBT_DEVICEQUERYREMOVEFAILED:
        {
            system("CLS");
            cout << "\033[38;5;196mНевозможно безопасно извлечь\033[0m" << endl;
            showMenu();
            listDevices();
            break;
        }
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

DWORD WINAPI InitThread(void*) {
    WNDCLASSEX wx = { sizeof(WNDCLASSEX), 0, WindowProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"USBMonitor", nullptr };
    RegisterClassEx(&wx);

    HWND hwnd = CreateWindow(L"USBMonitor", L"", WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    if (!hwnd) return -1;

    DEV_BROADCAST_DEVICEINTERFACE filter = { sizeof(filter), DBT_DEVTYP_DEVICEINTERFACE, 0, GUID_DEVINTERFACE_USB_DEVICE };
    RegisterDeviceNotification(hwnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE);

    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, nullptr, nullptr, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) return -1;

    showMenu();

    SP_DEVINFO_DATA deviceInfoData = { sizeof(SP_DEVINFO_DATA) };
    for (int i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); ++i) {
        USBDevice device(deviceInfoSet, deviceInfoData, hwnd);
        devicesList.push_back(device);
        cout << devicesList.size() << ". ";
        device.displayDeviceInfo();
    }
    SetupDiDestroyDeviceInfoList(deviceInfoSet);

    MSG msg;
    while (!exitFlag) {
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    HANDLE thread = CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    if (!thread) {
        cerr << "Failed to create thread." << endl;
        return 1;
    }

    while (true) {
        char ch = _getch();
        if (ch == '0') {
            exitFlag = true;
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);
            for (const auto& device : devicesList) {
                USBDevice::removeDevice(device);
            }
            break;
        }

        if (ch >= '1' && ch <= '9') {
            int index = ch - '1';
            if (index < devicesList.size()) {
                USBDevice& device = devicesList[index];
                if (device.isEjectable) {
                    device.isSafeRemovalInitiated = true;
                    device.ejectDevice();
                }
                else {
                    system("cls");
                    cout << "Устройство неизвлекаемое.\n";
                    showMenu();
                    listDevices();
                }
                Sleep(100);
            }
        }
    }
    return 0;
}