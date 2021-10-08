#pragma once
#include "md5.h"
#include "wmi/wmi.hpp"
#include "wmi/wmiclasses.hpp"
#include "debug.h"

#include <intrin.h> //__cpuid
#include <Windows.h>
#include <winuser.h>
#include <iostream>
using namespace std;
using namespace Wmi;

extern "C" __declspec(dllexport) const char* getIdentifier();

#define __abs(x) (x < 0 ? -(x) : x)

class HwidGrabber
{
public:
	HwidGrabber();
	~HwidGrabber();

	string getHwid();
private:
	string getDriveSerial(const char* drive);
	string getGpuid();
	string getBoardid();
	string getComputerName();
	string getNetworkid();
	string getCpuHash();
};
