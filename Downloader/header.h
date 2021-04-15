#pragma once

#include "header.h"

#include "console.hpp"
#include "md5file.h"
#include "util.h"
#include "network.h"
#include "spinner.h"
#include "CCallback.h"

#include <thread>
#include <chrono>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <WinInet.h>


#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")

using namespace std;

#define slp(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#define exp(x) std::exception(x,GetLastError());