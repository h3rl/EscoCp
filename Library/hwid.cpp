#include "hwid.h"
#include <intrin.h> //__cpuid
#include <stdio.h>

const char* strToCStr(string input)
{
	size_t size = sizeof(char) * (input.size() + 1);
	char* buff = (char*)malloc(size);
	if (buff) {
		sprintf_s(buff, size, "%s", input.c_str());
	}
	return buff;
}

string parseWql(string* src, const char* str)
{
	size_t start = src->find(str) + strlen(str);
	size_t len = src->find("&", start) - start;
	return src->substr(start, len);
}

string getDriveSerial(const char* drive)
{
	//First part gets the HDD informations
	DWORD serialNumber = -1;
	GetVolumeInformationA(
		drive,
		NULL,
		NULL,
		&serialNumber,
		NULL,
		NULL,
		NULL,
		NULL);
	return to_string(serialNumber);
}

string getGpuid()
{
	auto gpu = retrieveWmi<Win32_VideoController>();
	string subsys = parseWql(&gpu.PNPDeviceID, "SUBSYS_");
	string dev = parseWql(&gpu.PNPDeviceID, "DEV_");

	return string(subsys + dev);
}

string getBoardid()
{
	Win32_BaseBoard bboard = retrieveWmi<Win32_BaseBoard>();
	return bboard.SerialNumber;
}

string getComputerName()
{
	char computerName[64];
	DWORD size = sizeof(computerName);
	GetComputerNameA(computerName, &size);
	return string(computerName);
}

string getNetworkid()
{
	string macsum = "";
	for (const Win32_NetworkAdapter& service : retrieveAllWmi<Win32_NetworkAdapter>())
	{
		if (service.PNPDeviceID.find("PCI\\") != -1)
		{
			//cout << service.Description << endl;
			string mac = service.MACAddress;
			mac.erase(remove(mac.begin(), mac.end(), ':'), mac.end());
			macsum += mac;
		}
	}
	return macsum;
}

string getCpuHash()
{
	int hash = 5;
	int cpuinfo[4] = { 0, 0, 0, 0 }; //32 * 4
	__cpuid(cpuinfo, 0);

	for (int s = 0; s < 4; s++)
	{
		hash += cpuinfo[s] + (s << 2);
	}
	if (hash < 0)
		hash *= -1;
	return string(to_string(hash));
}

const char* getIdentifier()
{
	string cpu, drive, gpu, board, mac;
	//string cname;

	cpu = getCpuHash();
	drive = getDriveSerial("c:\\");
	//cname = getComputerName();

	//	wmi functions
	try {
		gpu = getGpuid();
		board = getBoardid();
		mac = getNetworkid();
	}
	catch (const WmiException& ex)
	{
		_D("error: " << ex.errorMessage.c_str() << "\ncode: " << ex.errorCode << " (" << ex.hexErrorCode() << ")");

		string err = "An error occured while grabbing identifiers, code " + ex.hexErrorCode() + "\nPlease contact support!";
		MessageBoxA(NULL, strToCStr(err), "ERROR", MB_OK | MB_ICONERROR);
		return "";
	}
	//_D("cname: " << cname << "\n");

	_D("cpu: " << cpu);
	_D("drive: " << drive);
	_D("gpu: " << gpu);
	_D("board: " << board);
	_D("mac: " << mac << endl);

	string prehwid = mac + gpu + cpu + board + drive;
	string hwid = md5(prehwid);

	_D("prehwid: " << prehwid);
	_D("hwid: " << hwid << endl);

	return strToCStr(hwid);
}