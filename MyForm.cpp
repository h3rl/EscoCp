#include "MyForm.h"
#include "debug.h"

#include <thread>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

void handlerThread()
{
	MSG msg{ 0 };
	//our application loop
	while (GetMessage(&msg, NULL, 0, 0) != 0);
	return;
}

Handler* pHandler = new Handler();

void Main(array<String^>^ args)
{
	createDbgConsole();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	HHOOK hook = ::SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, NULL);
	HANDLE hHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)handlerThread, 0, 0, 0);

	EscoCp::MyForm^ form = gcnew EscoCp::MyForm();
	form->setHandler(pHandler);
	form->startThreads();

	System::Windows::Forms::Application::Run(form);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	_D("CALLED");
	if (nCode < 0)
		return NULL;
	if (pHandler == NULL)
		return NULL;

	LPKBDLLHOOKSTRUCT keyStruct = (LPKBDLLHOOKSTRUCT)lParam;

	if ((keyStruct->flags >> LLKHF_INJECTED) & 1) {
		// ignore injected events
	}
	else {
		DWORD key = keyStruct->vkCode;
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {

			if (!pHandler->m_pKeys->at(key)) {
				pHandler->m_pKeys->at(key) = true;

				if (pHandler->m_bCaptureKey) {
					_D("hhas");
					pHandler->m_clParam = lParam;
					pHandler->m_bCaptureKey = false;
				}

				switch (key)
				{
				case VK_SPACE: {
					pHandler->stance = STANDING;
					break;
				}
				case VK_KEY_1: {
					pHandler->slot = SLOT1;
					break;
				}
				case VK_KEY_2: {
					pHandler->slot = SLOT2;
					break;
				}
				case VK_KEY_J:
				case VK_KEY_H:
				case VK_KEY_G: {
					pHandler->slot = NOSLOT;
					pHandler->lastSlot = NOSLOT;
					break;
				}
				case VK_KEY_X: {
					if (pHandler->slot == NOSLOT) {
						pHandler->slot = pHandler->lastSlot;
					}
					else {
						pHandler->lastSlot = pHandler->slot;
						pHandler->slot = NOSLOT;
					}
					break;
				}
				case VK_KEY_C: {
					if (pHandler->stance == STANDING || pHandler->stance == PRONE) {
						pHandler->stance = CROUCH;
					}
					else if (pHandler->stance == CROUCH) {
						pHandler->stance = STANDING;
					}
					break;
				}
				case VK_KEY_Z: {
					if (pHandler->stance == PRONE) {
						pHandler->stance = STANDING;
					}
					else {
						pHandler->stance = PRONE;
					}
					break;
				}
				case VK_DIVIDE: {
					pHandler->status.visible = !pHandler->status.visible;
					break;
				}
				case VK_HOME: {
					pHandler->status.reloadcfg = !pHandler->status.reloadcfg;
					break;
				}
				default:
					break;
				}
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			pHandler->m_pKeys->at(key) = false;
			break;
		}
		default:
			break;
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}