#include "input.h"

#include <windows.h>
#include <thread>

namespace input {
	void move(short x, short y) {
		mouse_event(MOUSEEVENTF_MOVE, x, y, NULL, NULL);
	}
	void move(short x, short y, int steps, int delay)
	{
		int dx = 0, dy = 0, dt = 0;

		for (int s = 1; s <= steps; ++s) {
			int sx = s * x / steps;
			int sy = s * y / steps;
			int st = s * delay / steps;
			move(sx - dx, sy - dy);
			std::this_thread::sleep_for(std::chrono::milliseconds(st - dt));
			dx = sx;
			dy = sy;
			dt = st;
		}
	}

	void SetMousePos(int x, int y) {
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, NULL, NULL);
		//maxmin 0 and 65,535

	}

	void click(short delay) {
		MouseButtonLDown();
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		MouseButtonLUp();
	}

	void MouseButtonLDown() {
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, NULL, NULL);
	}
	void MouseButtonLUp() {
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, NULL, NULL);
	}

	void pressKey(int vkey, int delay) {
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wVk = vkey;
		SendInput(1, &ip, sizeof(INPUT)); //pressing key
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT)); //releasing key
	}
}