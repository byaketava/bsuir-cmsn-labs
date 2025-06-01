#include <winsock2.h>
#include <ws2bth.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip> 
#include <list>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct BluetoothDeviceInfo {
    SOCKADDR_BTH btAddr;
    string deviceName;
    string serviceClassId;
};

list<BluetoothDeviceInfo> discoveredDevices;

void InitializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Failed to initialize Winsock." << endl;
        exit(EXIT_FAILURE);
    }
}

void DiscoverBluetoothDevices() {
    InitializeWinsock();

    HANDLE handleLookup;
    WSAQUERYSET querySet = { 0 };
    querySet.dwSize = sizeof(querySet);
    querySet.dwNameSpace = NS_BTH;

    if (WSALookupServiceBegin(&querySet, LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_RETURN_NAME | LUP_RETURN_TYPE, &handleLookup) != 0) {
        cerr << "Failed to begin Bluetooth lookup. Error code: " << WSAGetLastError() << endl;
        WSACleanup();
        return;
    }

    char buffer[4096];
    DWORD bufferLength = sizeof(buffer);
    WSAQUERYSET* results = reinterpret_cast<WSAQUERYSET*>(buffer);

    int index = 0;
    bool deviceFound = false;

    cout << left
        << setw(5) << "No"
        << setw(30) << "Device Name"
        << setw(20) << "Bluetooth Address"
        << setw(40) << "Service Class ID"
        << "\n";
    cout << string(95, '-') << "\n";

    while (true) {
        if (WSALookupServiceNext(handleLookup, LUP_RETURN_ADDR | LUP_RETURN_NAME | LUP_RETURN_TYPE, &bufferLength, results) != 0) {
            if (WSAGetLastError() == WSA_E_NO_MORE) {
                break;
            }
            else {
                cerr << "Failed to get next Bluetooth device. Error code: " << WSAGetLastError() << endl;
                break;
            }
        }

        SOCKADDR_BTH* btAddr = reinterpret_cast<SOCKADDR_BTH*>(results->lpcsaBuffer->RemoteAddr.lpSockaddr);
        BluetoothDeviceInfo device;
        device.btAddr = *btAddr;

        if (results->lpszServiceInstanceName && results->lpszServiceInstanceName[0] != L'\0') {
            wstring wideName(results->lpszServiceInstanceName);
            device.deviceName = string(wideName.begin(), wideName.end());
        }
        else {
            device.deviceName = "Unnamed Device";
        }

        if (results->lpServiceClassId) {
            GUID serviceClassId = *results->lpServiceClassId;

            ostringstream ss;
            ss << hex << uppercase
                << serviceClassId.Data1 << "-"
                << serviceClassId.Data2 << "-"
                << serviceClassId.Data3 << "-"
                << hex << static_cast<int>(serviceClassId.Data4[0])
                << static_cast<int>(serviceClassId.Data4[1]) << "-"
                << static_cast<int>(serviceClassId.Data4[2])
                << static_cast<int>(serviceClassId.Data4[3])
                << static_cast<int>(serviceClassId.Data4[4])
                << static_cast<int>(serviceClassId.Data4[5])
                << static_cast<int>(serviceClassId.Data4[6])
                << static_cast<int>(serviceClassId.Data4[7]);
            device.serviceClassId = ss.str();
        }
        else {
            device.serviceClassId = "Not Available";
        }

        discoveredDevices.push_back(device);
        deviceFound = true;

        cout << left
            << setw(5) << ++index
            << setw(30) << device.deviceName
            << setw(20) << hex << uppercase << btAddr->btAddr
            << setw(40) << device.serviceClassId
            << "\n";
    }

    if (!deviceFound) {
        cout << "No Bluetooth devices found.\n";
    }
    else {
        cout << "-------------------------------------\n";
        cout << "Bluetooth device scan completed.\n";
    }

    WSALookupServiceEnd(handleLookup);
    WSACleanup();
}

void SendFileData(const char* filePath, const SOCKADDR_BTH& targetAddress) {
    SOCKET btSocket = INVALID_SOCKET;
    ifstream file(filePath, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    InitializeWinsock();

    btSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (btSocket == INVALID_SOCKET) {
        cerr << "Failed to create Bluetooth socket." << endl;
        WSACleanup();
        return;
    }

    if (connect(btSocket, (SOCKADDR*)(&targetAddress), sizeof(targetAddress)) == SOCKET_ERROR) {
        cerr << "Connection failed." << endl;
        closesocket(btSocket);
        WSACleanup();
        return;
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        int bytesSent = send(btSocket, buffer, file.gcount(), 0);
        system("cls");
        cout << "Bytes sent: " << bytesSent << endl;
        if (bytesSent == SOCKET_ERROR) {
            cerr << "Failed to send data." << endl;
            break;
        }
    }

    if (file.gcount() > 0) {
        int bytesSent = send(btSocket, buffer, file.gcount(), 0);
        system("cls");
        cout << "Bytes sent: " << bytesSent << endl;
        if (bytesSent == SOCKET_ERROR) {
            cerr << "Failed to send remaining data." << endl;
        }
        else {
            cout << "File transfer completed successfully." << endl;
        }
    }
    file.close();

    this_thread::sleep_for(chrono::seconds(10));
    closesocket(btSocket);
    WSACleanup();
}

void ReceiveFileData(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived;
    ofstream file("received_file.mp3", ios::binary);

    if (!file.is_open()) {
        cerr << "Error creating file." << endl;
        return;
    }

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        file.write(buffer, bytesReceived);
        system("cls");
        cout << "Bytes received: " << bytesReceived << endl;
    }

    if (bytesReceived < 0) {
        cerr << "Error receiving data." << endl;
    }

    file.close();
    system("start received_file.mp3");
}

void StartServer() {
    SOCKET serverSocket = INVALID_SOCKET;
    SOCKADDR_BTH serverAddr = { 0 };

    InitializeWinsock();

    serverSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Failed to create server socket." << endl;
        WSACleanup();
        return;
    }

    serverAddr.addressFamily = AF_BTH;
    serverAddr.port = 11;
    serverAddr.serviceClassId = RFCOMM_PROTOCOL_UUID;

    if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Failed to bind server socket." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cerr << "Failed to listen on server socket." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Server started. Waiting for incoming connections..." << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Failed to accept incoming connection. Error: " << WSAGetLastError() << endl;
            continue;
        }

        cout << "Connection established." << endl;

        try {
            ReceiveFileData(clientSocket);
        }
        catch (...) {
            cerr << "An error occurred during file reception. Waiting for new connections..." << endl;
            continue;
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
}

void StartClient() {
    DiscoverBluetoothDevices();
    if (discoveredDevices.empty()) {
        cerr << "No Bluetooth devices found." << endl;
        return;
    }

    cout << "Choose device (1-" << discoveredDevices.size() << "): ";
    int selectedDeviceIndex;
    cin >> selectedDeviceIndex;

    if (selectedDeviceIndex < 1 || selectedDeviceIndex > discoveredDevices.size()) {
        cerr << "Invalid device selection." << endl;
        return;
    }

    auto it = discoveredDevices.begin();
    advance(it, selectedDeviceIndex - 1);

    BluetoothDeviceInfo remoteDevice = *it;
    SOCKADDR_BTH remoteAddress = remoteDevice.btAddr;
    remoteAddress.serviceClassId = RFCOMM_PROTOCOL_UUID;
    remoteAddress.port = 11;


    cout << "Sending file..." << endl;
    SendFileData("D:\\zima.mp3", remoteAddress);
}

int main() {
    int mode;
    setlocale(LC_ALL, "");
    cout << "Select mode:\n1. Server\n2. Client\n";
    cin >> mode;

    if (mode == 1) {
        StartServer();
    }
    else if (mode == 2) {
        StartClient();
    }
    else {
        cerr << "Invalid choice." << endl;
    }

    return 0;
}
