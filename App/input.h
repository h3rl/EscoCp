#pragma once
namespace input {
	void move(short x, short y);
	void SetMousePos(int x, int y);
	void click(short delay);
	void pressKey(int vkey, int delay);

	void MouseButtonLDown();
	void MouseButtonLUp();
}