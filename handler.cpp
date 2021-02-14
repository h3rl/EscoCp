#include "handler.h"
#include "MyForm.h"

Handler::Handler() {
	m_bCaptureKey = false;
	m_hHook = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, NULL);
	
	if (m_hHook)
		_S("Keyboard Hooked");
	else {
		_E("Keyboard Hook");
		_D("er:" << GetLastError());
		delete this;
	}
	
	m_handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)handlerThread, 0, 0, 0);
}

Handler::~Handler() {
	if (m_hHook) {
		UnhookWindowsHookEx(m_hHook);
		m_hHook = NULL;
	}
	if (m_handle) {
		TerminateThread(m_handle, 0);
	}
}

void Handler::handlerThread()
{
	MSG msg{ 0 };
	//our application loop
	while (GetMessage(&msg, NULL, 0, 0) != 0);
	return;
}