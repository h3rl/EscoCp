#include "debug.h"

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
	void move(short x, short y) {
		mouse_event(MOUSEEVENTF_MOVE, x, y, NULL, NULL);
	}
}

int main()
{
    static int smooth = 10;
    static int force = 2;
    static int time = 4;

    while (true)
    {
        try {
            if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON))
            {
                do {
                    input::move(0, 4);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                } while (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON));
            }
        }
        catch(std::exception ex) {
            _M(ex.what());
        };
    }
}