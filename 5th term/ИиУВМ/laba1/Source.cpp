#include <iostream>
#include <string>
#include <windows.h>
#include <powrprof.h>
#include <thread>
#include <Poclass.h>
#include <Setupapi.h>
#include <devguid.h>
#include <conio.h> 

#pragma comment (lib, "PowrProf.lib")
#pragma comment (lib, "setupapi.lib")

using namespace std;

char option = '0';
bool running = true;

string converter(int time) {
    int hours = time / 3600;
    int minutes = (time - hours * 3600) / 60;
    int seconds = time - hours * 3600 - minutes * 60;
    return to_string(hours) + "h " + to_string(minutes) + "min " + to_string(seconds);
}

void batteryType() {
    // Дескриптор, который используется для хранения списка устройств
    HDEVINFO batteryDeviceSet;
    // Функция SetupDiGetClassDevs запрашивает набор устройств класса "батарея"
    // &GUID_DEVCLASS_BATTERY указывает на класс устройств "батарея".
    // параметры 0 и DIGCF_PRESENT | DIGCF_DEVICEINTERFACE указывают,
    // что нужно получить только существующие устройства с интерфейсом
    batteryDeviceSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    // хранит информацию об интерфейсе, должна быть инициализирована перед использованием
    SP_DEVICE_INTERFACE_DATA batteryInterfaceData = { 0 };
    batteryInterfaceData.cbSize = sizeof(batteryInterfaceData);
    // перечисление интерфейсов устройств
    SetupDiEnumDeviceInterfaces(batteryDeviceSet, 0, &GUID_DEVCLASS_BATTERY, 0, &batteryInterfaceData);
    DWORD requiredSize = 0;
    // детальная информация (получение размера)
    SetupDiGetDeviceInterfaceDetail(batteryDeviceSet, &batteryInterfaceData, 0, 0, &requiredSize, 0);
    // выделяет память для хранения детальной информации
    PSP_DEVICE_INTERFACE_DETAIL_DATA batteryDetails = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, requiredSize);
    batteryDetails->cbSize = sizeof(*batteryDetails);
    // детальная информация (заполнение)
    SetupDiGetDeviceInterfaceDetail(batteryDeviceSet, &batteryInterfaceData, batteryDetails, requiredSize, &requiredSize, 0);
    // дескриптор (открытие устройства)
    HANDLE hBatteryDevice = CreateFile(batteryDetails->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // это структура для запроса информации о батарее, получение тега
    BATTERY_QUERY_INFORMATION batteryInfoQuery = { 0 };
    DeviceIoControl(hBatteryDevice, IOCTL_BATTERY_QUERY_TAG, 0, 0, &batteryInfoQuery.BatteryTag,
        sizeof(batteryInfoQuery.BatteryTag), 0, NULL) && batteryInfoQuery.BatteryTag;
    // структура для информации и получение информации
    BATTERY_INFORMATION batteryDetailsInfo = { 0 };
    batteryInfoQuery.InformationLevel = BatteryInformation;
    DeviceIoControl(hBatteryDevice, IOCTL_BATTERY_QUERY_INFORMATION, &batteryInfoQuery, sizeof(batteryInfoQuery),
        &batteryDetailsInfo, sizeof(batteryDetailsInfo), 0, 0);
    // тип батареи
    for (int i = 0; i < 4; i++)
    {
        cout << batteryDetailsInfo.Chemistry[i];
    };
    // освобождение ресурсов
    CloseHandle(hBatteryDevice);
    LocalFree(batteryDetails);
    SetupDiDestroyDeviceInfoList(batteryDeviceSet);
}

void batteryInfo() {
    // получение информации о состоянии питания
    SYSTEM_POWER_STATUS powerStatus;
    GetSystemPowerStatus(&powerStatus);
    int currentLevel = powerStatus.BatteryLifePercent;
    cout << "Battery charge level:\t\t";

    if (currentLevel > 50) {
        cout << "\033[1;5;38;5;119m" << currentLevel << "%\033[0m" << endl;
    }
    else if (currentLevel > 20) {
        cout << "\033[1;5;38;5;227m" << currentLevel << "%\033[0m" << endl;
    }
    else {
        cout << "\033[1;5;38;5;203m" << currentLevel << "%\033[0m" << endl;
    }

    if (powerStatus.SystemStatusFlag == 1) {
        cout << "Current energy saving mode:\t\033[1;5;38;5;227mON\033[0m" << endl;
    }
    else cout << "Current energy saving mode:\t\033[1;5;38;5;203mOFF\033[0m" << endl;

    if (powerStatus.ACLineStatus != 1) {
        cout << "Type of power supply:\t\t\033[1;5;38;5;039mBattery\033[0m" << endl;
        
        int batteryLifeTime = powerStatus.BatteryLifeTime;
        cout << "Remaining battery lifetime:\t\033[1;5;38;5;227m" << converter(batteryLifeTime) << "s\033[0m" << endl;
        
        int fullBatteryLifeTime = (100 * batteryLifeTime) / currentLevel;
        cout << "Battery lifetime at 100%:\t\033[1;5;38;5;227m" << converter(fullBatteryLifeTime) << "s\033[0m" << endl;
        cout << "Elapsed battery lifetime:\t\033[1;5;38;5;227m" << converter(fullBatteryLifeTime - batteryLifeTime) << "s\033[0m" << endl;
    }
    else {
        cout << "Type of power supply:\t\t\033[1;5;38;5;039mAC\033[0m\n";
    }

    cout << "Battery Type:\t\t\t\033[1;5;38;5;039m";
    batteryType();
    cout << "\033[0m" << endl << endl;
}

void updateBatteryInfo() {
    while (running) {
        system("cls");
        batteryInfo();
        cout << "To EXIT enter 4:  ";
        // Проверяем, был ли введен символ
        if (_kbhit()) {
            char option = _getch(); // Считываем символ
            cout << option << endl; // Выводим считанный символ для проверки
            if (option == '4')
                break;
        }
        Sleep(1000);
    }
}

void displayMenu() {
    while (running) {
        cout << " _______________________ \n";
        cout << "|\t\033[1;5;38;5;227mBATTERY\033[0m\t\t|\n";
        cout << "|-----------------------|\n";
        cout << "|\033[1;5;38;5;227m1)\033[0m Battery info\t|\n|\033[1;5;38;5;227m2)\033[0m Sleep mode\t\t|\n|\033[1;5;38;5;227m3)\033[0m Hibernation\t\t|\n|\033[1;5;38;5;227m4)\033[0m Exit\t\t|\n";
        cout << "|_______________________|\n\n";
        cout << "Option: ";
        cin >> option;
        switch (option) {
        case '1':
            updateBatteryInfo();
            break;
        case '2':
            SetSuspendState(0, 0, 0);
            break;
        case '3':
            SetSuspendState(1, 0, 0);
            break;
        case '4':
            running = false;
            break;
        default:
            cout << "Incorrect! Try again!\n";
        }
        system("cls");
    }
}  

int main() {
    displayMenu();
    return 0;
}