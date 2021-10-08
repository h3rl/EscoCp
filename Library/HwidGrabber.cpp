#include "HwidGrabber.h"
#include <intrin.h> //__cpuid
#include <stdio.h>

HwidGrabber::HwidGrabber()
{
}

HwidGrabber::~HwidGrabber()
{
}

string HwidGrabber::getHwid()
{
	return getCpuHash();
	/*
		string drive = getDriveSerial("C:\\");
		string gpu = getGpuid();
		string mboard = getBoardid();
		string cname = getComputerName();
		string net = getNetworkid();
		string cpu = getCpuHash();

		_D("drive: " << drive);
		_D("gpu: " << gpu);
		_D("mboard: " <<mboard);
		//_D("cname: " << id.cname);
		_D("net: " << net);
		_D("cpu: " << cpu);

		string hwid = gpu + cpu + mboard + net + drive;
		string hwidhashed = md5(hwid);

		_D(endl);
		_D("prehwid: " << hwid);
		_D("hwid: " << hwidhashed);

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
	*/

	

    return nullptr;
}

string HwidGrabber::getDriveSerial(const char* drive)
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

string HwidGrabber::getGpuid()
{
	Win32_VideoController gpu = retrieveWmi<Win32_VideoController>();

	size_t start, len;
	string search = "SUBSYS_";
	string* src = &gpu.PNPDeviceID;

	start = src->find(search) + search.length();
	len = src->find("&", start) - start;
	string subsys = src->substr(start, len);

	search = "DEV_";

	start = src->find(search) + search.length();
	len = src->find("&", start) - start;
	string dev = src->substr(start, len);

	return string(subsys + dev);
}

string HwidGrabber::getBoardid()
{
	Win32_BaseBoard bboard = retrieveWmi<Win32_BaseBoard>();
	return bboard.SerialNumber;
}

string HwidGrabber::getComputerName()
{
    return nullptr;
}

string HwidGrabber::getNetworkid()
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

string HwidGrabber::getCpuHash()
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
	HwidGrabber* hg = new HwidGrabber();

	string hwid = hg->getHwid();

	char* writable = new char[hwid.size() + 1];

	copy(hwid.begin(), hwid.end(), writable);

	writable[hwid.size()] = '\0'; // don't forget the terminating 0
	return writable;
}