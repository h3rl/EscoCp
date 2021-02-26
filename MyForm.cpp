#include "MyForm.h"
#include "debug.h"
//#include "hwid.h"

#include <thread>

using namespace System;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Threading;


HWND gHwnd = NULL;
Handler* pHandler = nullptr;
Config* pConfig = nullptr;
HANDLE m_hRecoil;

void recoilThread();

void Main(array<String^>^ args)
{
	createDbgConsole();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	pHandler = new Handler();
	pConfig = new Config();
	EscoCp::MyForm^ form = gcnew EscoCp::MyForm();
	form->setConfig(pConfig);
	form->setHandler(pHandler);
	gHwnd = form->getHwnd();
	m_hRecoil = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recoilThread, 0, 0, 0);
	if (m_hRecoil) {
		SetThreadPriority(m_hRecoil, THREAD_PRIORITY_ABOVE_NORMAL);
	}
	else {
		String^ err = "Failed to create threads\ncode: " + GetLastError();
		MessageBoxA(NULL,sysToCstr(err), "error", MB_OK);
		return;
	}
	System::Windows::Forms::Application::Run(form);
	
}

void recoilThread()
{
	_S("recoil thread started");
	for (;;)
	{
		if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON) && pHandler->slot != NOSLOT && pHandler->profiles.at(pHandler->slot) != nullptr)
		{
			//_D(pHandler->profiles.at(pHandler->slot)->name << " Slot " << pHandler->slot << " " << stringifyStance(pHandler->stance, false));
			_D("shoot");
			int force, delay;
			do {
				force = max(pHandler->profiles.at(pHandler->slot)->recoil.at(pHandler->stance),0);
				delay = max(pHandler->profiles.at(pHandler->slot)->delay.at(pHandler->stance),1);
				input::move(0, force);
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			} while (GetAsyncKeyState(VK_LBUTTON) && pHandler->slot != NOSLOT && pHandler->profiles.at(pHandler->slot) != nullptr);
			_D("noshoot");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (pHandler == NULL) {
		return NULL;
	}
	if (nCode < 0) {
		return CallNextHookEx(pHandler->m_hHook,nCode,wParam,lParam);
	}

	LPKBDLLHOOKSTRUCT keyStruct = (LPKBDLLHOOKSTRUCT)lParam;

	if ((keyStruct->flags >> LLKHF_INJECTED) & 1) {
		// ignore injected events
	}
	else {
		DWORD key = keyStruct->vkCode;
		//insert if key not in map
		if (!pHandler->m_pKeys->count(key)) {
			pHandler->m_pKeys->insert({ key,false });
		}
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			if (!pHandler->m_pKeys->at(key)) {
				pHandler->m_pKeys->at(key) = true;

				for (size_t i = 0; i < pConfig->profileList.size(); i++) {
					Profile* profile = &pConfig->profileList.at(i);
					if (profile->onkey == key && pHandler->slot != NOSLOT ) {
						pHandler->profiles.at(pHandler->slot) = &pConfig->profileList.at(i);
						_D("SET " << profile->name << " to slot " << pHandler->slot);
					}
				}
				if (key == pConfig->vanishkey) {
					pConfig->vanish = !pConfig->vanish;
					ShowWindow(gHwnd, pConfig->vanish ? SW_HIDE : SW_SHOW);
					_D("SET gui " << (pConfig->vanish ? "hidden" : "visible"));
				}
				switch (key)
				{
				case VK_SPACE: {
					pHandler->stance = STANDING;
					_D("SET stance " << stringifyStance( pHandler->stance , true));
					break;
				}
				case VK_KEY_1: {
					pHandler->slot = SLOT1;
					_D("SET slot 1");
					break;
				}
				case VK_KEY_2: {
					pHandler->slot = SLOT2;
					_D("SET slot 2");
					break;
				}
				case VK_KEY_J:
				case VK_KEY_H:
				case VK_KEY_G: {
					_D("SET slot NOSLOT");
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
					_D("SET slot " << pHandler->slot);
					break;
				}
				case VK_KEY_C: {
					if (pHandler->stance == STANDING || pHandler->stance == PRONE) {
						pHandler->stance = CROUCH;
					}
					else if (pHandler->stance == CROUCH) {
						pHandler->stance = STANDING;
					}
					_D("SET stance " << stringifyStance(pHandler->stance, true));
					break;
				}
				case VK_KEY_Z: {
					if (pHandler->stance == PRONE) {
						pHandler->stance = STANDING;
					}
					else {
						pHandler->stance = PRONE;
					}
					_D("SET stance " << stringifyStance(pHandler->stance, true));
					break;
				}
				/*
				case VK_DIVIDE: {
					pHandler->status.visible = !pHandler->status.visible;
					break;
				}
				case VK_HOME: {
					pHandler->status.reloadcfg = !pHandler->status.reloadcfg;
					break;
				}
				*/
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
	return CallNextHookEx(pHandler->m_hHook, nCode, wParam, lParam);
}