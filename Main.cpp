#include <iostream>
#include <Windows.h>
#include <fstream>
#include<string>
using namespace std;

#pragma warning(disable : 4996)

struct employee
{
	int num;
	char name[10];
	double hours;
};

LPWSTR stringToLPWSTR(string str) {
	wchar_t temp[256];
	mbstowcs(temp, str.c_str(), str.length());
	LPWSTR data = temp;
	return data;
}

void checkDataInFileBin(string filename, string count)
{
	system("cls");

	cout << "checking data in bin\n";

	int length = stoi(count);
	
	ifstream fin;
	fin.open(filename, ios::binary);


	for (int i = 0; i < length; i++) {
		employee empl;
		fin.read((char*)&empl, sizeof(struct employee));
		cout << empl.num << " " << empl.name << " " << empl.hours << endl;
	}

	
	fin.close();
}

void checkDataInFiletxt(string filename)
{
	system("cls");

	cout << "checking data in report\n";

	ifstream fin(filename);

	string temp;
	while (!fin.eof()) {
		getline(fin, temp);
		cout << temp << endl;
	}
	fin.close();
}

void runCreatorProcess(string str1)
{
	STARTUPINFO startUpInfo;
	PROCESS_INFORMATION procInfo;

	ZeroMemory(&startUpInfo, sizeof(startUpInfo));
	startUpInfo.cb = sizeof(startUpInfo);
	ZeroMemory(&procInfo, sizeof(procInfo));
	if (!CreateProcess(NULL, stringToLPWSTR(str1), NULL, NULL, FALSE, 0, NULL, NULL, &startUpInfo, &procInfo)) {
		cout << "CreateProcess is failed";
	}
	WaitForSingleObject(procInfo.hProcess, INFINITE);
	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);
}

void runReporterProcess(string str2)
{
	STARTUPINFO startUpInfo;
	PROCESS_INFORMATION procInfo;

	ZeroMemory(&startUpInfo, sizeof(startUpInfo));
	startUpInfo.cb = sizeof(startUpInfo);
	ZeroMemory(&procInfo, sizeof(procInfo));
	if (!CreateProcess(NULL, stringToLPWSTR(str2), NULL, NULL, FALSE, 0, NULL, NULL, &startUpInfo, &procInfo)) {
		cout << "CreateProcess is failed";
	}
	WaitForSingleObject(procInfo.hProcess, INFINITE);
	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);
}

int main()
{
	setlocale(LC_ALL, ".1251");
	string filename_bin;
	cout << "Enter the bin file name:\n";
	cin >> filename_bin;
	string count;
	cout << "Enter the count of empls:\n";
	cin >> count;
	string for_creator = "Creator " + filename_bin + " " + count;

	runCreatorProcess(for_creator);

	checkDataInFileBin(filename_bin, count);
	
	string filename_Otchet;
	string countOfHours;
	cout << "Enter the report file name:\n";
	cin >> filename_Otchet;
	cout << "Enter the salary per hour:\n";
	cin >> countOfHours;
	string for_reporter = "Reporter " + filename_bin + " " + filename_Otchet + " " + countOfHours;

	runReporterProcess(for_reporter);
	
	checkDataInFiletxt(filename_Otchet);
}
