#include "handler.h"
#include "form.h"

Handler::Handler() {
	ingame = false;
	slot = NOSLOT;
	lastSlot = NOSLOT;
	stance = STANDING;
	m_bCaptureKey = false;

	kbHook = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)kbProc, NULL, NULL);
	moHook = SetWindowsHookExA(WH_MOUSE_LL, (HOOKPROC)moProc, NULL, NULL);

	if (kbHook && moHook)
		_S("Hooks set");
	else {
		_E("Hooks failed");
		_D("er:" << GetLastError());
		delete this;
	}
	
	htMessage = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)messageThread, 0, 0, 0);
}

Handler::~Handler() {
	if (kbHook) {
		UnhookWindowsHookEx(kbHook);
		kbHook = NULL;
	}
	if (moHook) {
		UnhookWindowsHookEx(moHook);
		moHook = NULL;
	}
	if (htMessage) {
		TerminateThread(htMessage, 0);
	}
}

void Handler::messageThread()
{
	MSG msg{ 0 };
	//our application loop
	while (GetMessage(&msg, NULL, 0, 0) != 0);
	return;
}