#pragma comment(lib, "Setupapi.lib")
#include <iostream>
#include <Windows.h>
#include <Setupapi.h>
#include <devguid.h>
#include <cwchar>

#include <opencv2/opencv.hpp>﻿

using namespace std;
using namespace cv;

void displayWebcamInfo() {
	SP_DEVINFO_DATA deviceInfoData;
	WCHAR deviceName[256] = { 0 };
	WCHAR vendorName[256] = { 0 };
	WCHAR deviceInstanceID[256] = { 0 };
	HDEVINFO deviceInfoSet = SetupDiGetClassDevsA(&GUID_DEVCLASS_CAMERA, "USB", nullptr, DIGCF_PRESENT);
	if (deviceInfoSet == INVALID_HANDLE_VALUE)
		return;

	for (int i = 0; ; i++) {
		deviceInfoData.cbSize = sizeof(deviceInfoData);

		if (!SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData))
			break;

		if (!SetupDiGetDeviceInstanceIdW(deviceInfoSet, &deviceInfoData, deviceInstanceID, _countof(deviceInstanceID), nullptr)) {
			wcscpy_s(deviceInstanceID, L"Unknown");
		}
		if (!SetupDiGetDeviceRegistryPropertyW(deviceInfoSet, &deviceInfoData, SPDRP_FRIENDLYNAME, nullptr, (PBYTE)deviceName, sizeof(deviceName), nullptr)) {
			wcscpy_s(deviceName, L"Unknown");
		}
		if (!SetupDiGetDeviceRegistryPropertyW(deviceInfoSet, &deviceInfoData, SPDRP_MFG, nullptr, (PBYTE)vendorName, sizeof(vendorName), nullptr)) {
			wcscpy_s(vendorName, L"Unknown");
		}

		wcout << L" _____________________________________________________________ " << endl;
		wcout << L"|                        Camera " << i << L" info                        |" << endl;
		wcout << L"|_____________________________________________________________|" << endl;
		wcout << L"| Device Name | " << left << setw(46) << deviceName << L"|" << endl;
		wcout << L"|_____________|_______________________________________________|" << endl;
		wcout << L"| Vendor Name | " << left << setw(46) << vendorName << L"|" << endl;
		wcout << L"|_____________|_______________________________________________|" << endl;
		wcout << L"| Device ID   | " << left << setw(46) << deviceInstanceID << "|" << endl;
		wcout << L"|_____________|_______________________________________________|" << endl;

		SetupDiDeleteDeviceInfo(deviceInfoSet, &deviceInfoData);
	}
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

void TakePhoto(VideoCapture& camera) {
	Mat matrix;

	camera >> matrix;
	if (matrix.empty()) {
		cerr << "Error (cannot capture the frame)" << endl;
		return;
	}
	imwrite("photo.jpg", matrix);
	cout << "Photo saved to  D:\\vs\\5sem\\iiuvm\\laba4\\photo.jpg" << endl;
	destroyAllWindows();
}

void TakeAndSaveVideo(VideoCapture& camera) {
	Mat matrix;

	int width = static_cast<int>(camera.get(CAP_PROP_FRAME_WIDTH));
	int height = static_cast<int>(camera.get(CAP_PROP_FRAME_HEIGHT));

	VideoWriter videoWriter("video.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(width, height));

	if (!videoWriter.isOpened()) {
		cerr << "Error (cannot open video writer)" << endl;
		return;
	}

	while (true) {
		camera >> matrix;
		if (matrix.empty()) {
			cerr << "Error (cannot capture frame)" << endl;
			break;
		}

		videoWriter.write(matrix);

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			cout << "Recording finished" << endl;
			break;
		}
	}
	videoWriter.release();
	cout << "Video saved to D:\\vs\\5sem\\iiuvm\\laba4\\video.avi" << endl;
}

int main() {
	setlocale(LC_ALL, "");
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	displayWebcamInfo();

	while (true) {
		VideoCapture camera(0);

		if (!camera.isOpened()) {
			cerr << endl << "Error (cannot open a webcam)" << endl;
			return -1;
		}

		char choice;

		cout << endl << "Options:" << endl;
		cout << "1 - Take a photo" << endl;
		cout << "2 - Take a video (stop by pressing space button)" << endl;
		cout << "0 - Exit" << endl;

		cin >> choice;

		HWND hwnd = GetConsoleWindow();

		switch (choice) {
		case '1':
			ShowWindow(hwnd, SW_HIDE);
			TakePhoto(camera);
			ShowWindow(hwnd, SW_SHOWNORMAL);
			break;

		case '2':
			ShowWindow(hwnd, SW_HIDE);
			TakeAndSaveVideo(camera);
			ShowWindow(hwnd, SW_SHOWNORMAL);
			break;

		case '0':
			cout << endl << "End of the programm" << endl;
			camera.release();
			return 0;

		default:
			cout << "Invalid input, try again\n" << endl;
		}
		camera.release();
	}
	return 0;
}