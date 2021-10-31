#include "debug.h"
#include "util.h"

#include <Windows.h>
#include <iostream>
#include <fstream>

#include <string>
#include <map>
#include <vector>

//***C++11 Style:***
#include <chrono>
using std::chrono::steady_clock;
using namespace std;

#include <windows.h>
#include <thread>

namespace input {
	void move(int x, int y) {
		mouse_event(MOUSEEVENTF_MOVE, x, y, NULL, NULL);
	}
}

#define __slp(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

int main()
{
    int times = 7;
    int delay = 4;
    int force = 1;
    const int smooth = 5;
    for (;;)
    {
        if (GetAsyncKeyState(VK_KEY_K))
        {
            do {
                for (size_t i = 0; i < times; i++) {
                    input::move(0, force);
                    if (!GetAsyncKeyState(VK_KEY_K)) break;
                }
                __slp(delay);
            } while (GetAsyncKeyState(VK_KEY_K));
        }
        __slp(10);
    }
}