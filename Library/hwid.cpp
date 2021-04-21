#include <Windows.h>
#include <winuser.h>

#include "exports.h"
#include "md5.h"
#include "wmi/wmi.hpp"
#include "wmi/wmiclasses.hpp"
#include "debug.h"

#include <iostream>
using namespace std;
using namespace Wmi;

#pragma comment(lib, "wbemuuid.lib")

#include <intrin.h> //__cpuid

#define __abs(x) (x < 0 ? -(x) : x)


// parse and convert functions
const char* i2c(int* i, size_t size) {
	size_t s = sizeof(char) * size;

	char* buff = (char*)malloc(s);
	if (buff) {
		sprintf_s(buff, s, "%d", *i);
		return buff;
	}
	return "";
}

string parseWql(string* src, string str)
{
	size_t start = src->find(str) + str.length();
	size_t len = src->find("&", start) - start;
	return src->substr(start, len);
}

// identifiergrab functions

const char* getDriveSerial(const char* drive)
{
	//First part gets the HDD informations
	DWORD serialNumber = -1;
	if (GetVolumeInformationA(
		drive,
		NULL,
		NULL,
		&serialNumber,
		NULL,
		NULL,
		NULL,
		NULL))
	{
		return i2c((int*)&serialNumber, 16);
	}
	return "12312";
}

const char* getCpuHash()
{
	int hash = 5;
	int cpuinfo[4] = { 0, 0, 0, 0 }; //32 * 4
	__cpuid(cpuinfo, 0);

	for (size_t s = 0; s < 4; s++)
	{
		hash += cpuinfo[s] + (s << 2);
	}
	if (hash < 0)
		hash = hash * -1;

	return i2c(&hash, 32);
}

const char* getComputerName()
{
	char computerName[64];
	DWORD size = sizeof(computerName);
	GetComputerNameA(computerName, &size);
	if (sizeof(computerName) < size)
	{
		return "bigcompuper";
	}

	size_t s = sizeof(char) * 64;

	char* buff = (char*)malloc(s);
	if (buff) {
		sprintf_s(buff, s, "%s", computerName);
		return buff;
	}
	return "";
}

const char* getGpuid()
{
	Win32_VideoController gpu = retrieveWmi<Win32_VideoController>();
	string ret = string(parseWql(&gpu.PNPDeviceID, "SUBSYS_") + parseWql(&gpu.PNPDeviceID, "DEV_"));

	size_t size = sizeof(char) * 16;
	char* buff = (char*)malloc(size);

	if (buff) {
		sprintf_s(buff, size, "%s", ret.c_str());
		return buff;
	}
	return "";
}

const char* getBoardid()
{
	Win32_BaseBoard bboard = retrieveWmi<Win32_BaseBoard>();

	string ret = bboard.SerialNumber;

	size_t size = sizeof(char) * 16;
	char* buff = (char*)malloc(size);

	if (buff) {
		sprintf_s(buff, size, "%s", ret.c_str());
		return buff;
	}
	return "";
}

const char* getNetworkid()
{
	string ret = "";
	for (const Win32_NetworkAdapter& service : retrieveAllWmi<Win32_NetworkAdapter>())
	{
		if (service.PNPDeviceID.find("PCI\\") != -1)
		{
			//cout << service.Description << endl;
			string mac = service.MACAddress;
			mac.erase(remove(mac.begin(), mac.end(), ':'), mac.end());
			ret += mac;
		}
	}

	size_t size = sizeof(char) * (ret.length()+1);
	char* buff = (char*)malloc(size);

	if (buff) {
		sprintf_s(buff, size, "%s", ret.c_str());
		return buff;
	}
	return "";
}

struct Identifier
{
	string drive;
	string gpu;
	string cpu;
	string mboard;
	string cname;
	string net;
};

const char* getIdentifier()
{
	try {
		Identifier id;
		id.drive = getDriveSerial("C:\\");
		id.gpu = getGpuid();
		id.mboard = getBoardid();
		id.cname = getComputerName();
		id.net = getNetworkid();
		id.cpu = getCpuHash();

		_D("drive: " << id.drive);
		_D("gpu: " << id.gpu);
		_D("mboard: " << id.mboard);
		_D("cname: " << id.cname);
		_D("net: " << id.net);
		_D("cpu: " << id.cpu);

		string hwid = id.gpu + id.cpu + id.mboard + id.cname + id.net + id.drive;
		string hwidf = md5(hwid);

		_D(endl);
		_D("prehwid: " << hwid);

		size_t size = sizeof(char) * (hwidf.length() + 1);
		char* buff = (char*)malloc(size);

		if (buff) {
			sprintf_s(buff, size, "%s", hwidf.c_str());
			return buff;// Program successfully completed.
		}
	}
	catch (const WmiException& ex) {

		char buff[128];
		sprintf_s(buff, "error: %s, Code: %s", ex.errorMessage.c_str(), ex.hexErrorCode().c_str());
		cout << buff;

		MessageBoxA(NULL, buff, "Error", MB_OK | MB_ICONERROR);
		cerr << "error: " << ex.errorMessage << ", Code: " << ex.hexErrorCode() << endl;
	}
	return "ERROR";// Program failed
}