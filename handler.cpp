#include "handler.h"
#include "MyForm.h"

Handler::Handler() {
	slot = NOSLOT;
	lastSlot = NOSLOT;
	stance = STANDING;
	m_bCaptureKey = false;
	m_hHook = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, NULL);
	
	if (m_hHook)
		_S("Keyboard Hooked");
	else {
		_E("Keyboard Hook");
		_D("er:" << GetLastError());
		delete this;
	}
	
	m_hMessage = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)messageThread, 0, 0, 0);
}

Handler::~Handler() {
	if (m_hHook) {
		UnhookWindowsHookEx(m_hHook);
		m_hHook = NULL;
	}
	if (m_hMessage) {
		TerminateThread(m_hMessage, 0);
	}
}

void Handler::messageThread()
{
	MSG msg{ 0 };
	//our application loop
	while (GetMessage(&msg, NULL, 0, 0) != 0);
	return;
}