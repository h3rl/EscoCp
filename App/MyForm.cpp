#include "MyForm.h"
#include <debug.hpp>
//#include "hwid.h"

#include <library.h>

#include <thread>

using namespace System;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Threading;


HWND gHwnd;
Handler* pHandler = nullptr;
Config* pConfig = nullptr;
HANDLE hRecoil;
HANDLE hUpdate;

void recoilThread(); void updateThread();

void Main(array<String^>^ args)
{
	createDbgConsole();

	if (0 != strcmp("a0c6128e1fb4a5de6dcf420abc791fec", getIdentifier()))
	{
		return;
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	pHandler = new Handler();
	pConfig = new Config();
	EscoCp::MyForm^ form = gcnew EscoCp::MyForm();
	form->setConfig(pConfig);
	form->setHandler(pHandler);
	gHwnd = form->getHwnd();
	hRecoil = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recoilThread, 0, 0, 0);
	hUpdate = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)updateThread, 0, 0, 0);
	if (hRecoil && hUpdate) {
		SetThreadPriority(hRecoil, THREAD_PRIORITY_ABOVE_NORMAL);
	}
	else {
		String^ err = "Failed to create threads\ncode: " + GetLastError();
		MessageBoxA(NULL,sysToCstr(err), "error", MB_OK);
		return;
	}
	System::Windows::Forms::Application::Run(form);
}

void updateThread()
{
	bool b;
	for (;;)
	{
		if (pConfig->tabbedIn) {
			char string[32];
			GetWindowTextA(GetForegroundWindow(), string, sizeof(string));
			b = std::strstr(string, "TLEGR") != NULL;
		}
		else {
			b = true;
		}
		if (pHandler->ingame != b)
			pHandler->ingame = b;

		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	return;
}


void recoilThread()
{
	_S("recoil thread started");
	for (;;)
	{
		if (pHandler->ingame && pHandler->moKeys->at(VK_LBUTTON) && pHandler->moKeys->at(VK_RBUTTON) && pHandler->slot != NOSLOT && pHandler->profiles.at(pHandler->slot) != nullptr)
		{
			//_D(pHandler->profiles.at(pHandler->slot)->name << " Slot " << pHandler->slot << " " << stringifyStance(pHandler->stance));
			_D("shoot");
			int force, delay;
			do {
				force = max(pHandler->profiles.at(pHandler->slot)->recoil.at(pHandler->stance), 0);
				delay = max(pHandler->profiles.at(pHandler->slot)->delay.at(pHandler->stance), 1);
				input::move(0, force);
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			} while (pHandler->moKeys->at(VK_LBUTTON) && pHandler->slot != NOSLOT && pHandler->profiles.at(pHandler->slot) != nullptr);
			_D("noshoot");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}

LRESULT CALLBACK kbProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (pHandler == NULL) {
		return NULL;
	}
	if (nCode < 0) {
		return CallNextHookEx(pHandler->kbHook,nCode,wParam,lParam);
	}

	LPKBDLLHOOKSTRUCT keyStruct = (LPKBDLLHOOKSTRUCT)lParam;

	if ((keyStruct->flags >> LLKHF_INJECTED) & 1) {
		// ignore injected events
	}
	else {
		DWORD key = keyStruct->vkCode;
		//insert if key not in map
		if (!pHandler->kbKeys->count(key)) {
			pHandler->kbKeys->insert({ key,false });
		}
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			if (!pHandler->kbKeys->at(key)) {
				pHandler->kbKeys->at(key) = true;

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
					_D("SET stance " << stringifyStance( pHandler->stance));
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
					_D("SET stance " << stringifyStance(pHandler->stance));
					break;
				}
				case VK_KEY_Z: {
					if (pHandler->stance == PRONE) {
						pHandler->stance = STANDING;
					}
					else {
						pHandler->stance = PRONE;
					}
					_D("SET stance " << stringifyStance(pHandler->stance));
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
			pHandler->kbKeys->at(key) = false;
			break;
		}
		default:
			break;
		}
		
	}
	return CallNextHookEx(pHandler->kbHook, nCode, wParam, lParam);
}

#define _D(x)

void kmMacro(DWORD key)
{
	if (key == pConfig->vanishkey) {
		pConfig->vanish = !pConfig->vanish;
		ShowWindow(gHwnd, pConfig->vanish ? SW_HIDE : SW_SHOW);
		_D("SET gui " << (pConfig->vanish ? "hidden" : "visible"));
	}
}

LRESULT CALLBACK moProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (pHandler == NULL) {
		return NULL;
	}
	if (nCode < 0) {
		return CallNextHookEx(pHandler->moHook, nCode, wParam, lParam);
	}

	LPMSLLHOOKSTRUCT mStruct = (LPMSLLHOOKSTRUCT)lParam;

	if ((mStruct->flags >> LLKHF_INJECTED) & 1) {
		//ignore injected
	}
	else {
#define O(x) pHandler->moKeys->at(x)

		switch (wParam)
		{
		case WM_LBUTTONDOWN: {
			if (!O(VK_LBUTTON)) {
				O(VK_LBUTTON) = true;
				_D("Left_");
			}

			break;
		}
		case WM_LBUTTONUP: {
			if (O(VK_LBUTTON)) {
				O(VK_LBUTTON) = false;
				_D("Left^");
			}

			break;
		}
		case WM_RBUTTONDOWN: {
			if (!O(VK_RBUTTON)) {
				O(VK_RBUTTON) = true;
				_D("Right_");
			}
			break;
		}
		case WM_RBUTTONUP: {
			if (O(VK_RBUTTON)) {
				O(VK_RBUTTON) = false;
				_D("Right^");
			}
			break;
		}
		case WM_XBUTTONDOWN: {
			int ind = GET_XBUTTON_WPARAM(mStruct->mouseData);

			if (ind == 1) {
				if (!O(VK_XBUTTON1)) {
					O(VK_XBUTTON1) = true;
					_D("x1_");
					kmMacro(VK_XBUTTON1);
				}
			}else if (ind == 2) {
				if (!O(VK_XBUTTON2)) {
					O(VK_XBUTTON2) = true;
					_D("x2_");
					kmMacro(VK_XBUTTON2);
				}
			}
			break;
		}
		case WM_XBUTTONUP: {
			int ind = GET_XBUTTON_WPARAM(mStruct->mouseData);

			if (ind == 1) {
				if (O(VK_XBUTTON1)) {
					O(VK_XBUTTON1) = false;
					_D("x1^");
				}
			}
			else if (ind == 2) {
				if (O(VK_XBUTTON2)) {
					O(VK_XBUTTON2) = false;
					_D("x2^");
				}
			}
			break;
		}
		//case WM_MOUSEWHEEL: {
		//	_D((int)mStruct->mouseData);
		//	_D("vScroll " << ((int)mStruct->mouseData < 0 ? "down" : "up"));
		//	break;
		//}
		//case WM_MOUSEHWHEEL: {
		//	_D("hScroll" << ((int)mStruct->mouseData < 0 ? "left" : "right"));
		//	break;
		//}
		case WM_MBUTTONDOWN: {
			if (!O(VK_MBUTTON)) {
				O(VK_MBUTTON) = true;
				_D("Middle_");
				kmMacro(VK_MBUTTON);
			}
			break;
		}
		case WM_MBUTTONUP: {
			if (O(VK_MBUTTON)) {
				O(VK_MBUTTON) = false;
				_D("Middle^");
			}
			break;
		}
		case WM_MOUSEMOVE:
			break;
		default: {
			//_D(std::hex << wParam);
			break;
		}
		}
	}
	return CallNextHookEx(pHandler->moHook, nCode, wParam, lParam);
}