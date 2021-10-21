#pragma once
#include "md5.h"
#include "wmi/wmi.hpp"
#include "wmi/wmiclasses.hpp"
#include "debug.h"
#include "librarydefs.h"

#include <string>
using namespace std;
using namespace Wmi;

ESCOLIB_EXPORT const char* getIdentifier();

#define __abs(x) (x < 0 ? -(x) : x)

string getDriveSerial(const char* drive);
string getGpuid();
string getBoardid();
string getComputerName();
string getNetworkid();
string getCpuHash();
