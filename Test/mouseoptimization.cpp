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

#define slp(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

int main()
{
    int time = 10;
    int force = 5;

    const int smooth = 5;

    while (true)
    {
        try {
            int extra = time % smooth;
            int deltatime = (time - extra) / smooth;
            while(GetAsyncKeyState(VK_KEY_L)) {
                for (int i = 0; i < smooth; i++)
                {
                    input::move(0, force);
                    if (extra <= i) {
                        slp(deltatime+1)
                    }
                    else {
                        slp(deltatime)
                    }
                    
                    if (!GetAsyncKeyState(VK_KEY_L)) break;
                }
            }
            if (GetAsyncKeyState(VK_KEY_K)) break;
        }
        catch(std::exception ex) {
            _M(ex.what());
        };
    }
}