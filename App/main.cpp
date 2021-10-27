#include "MyForm.h"
#include "debug.h"

#include <library.h>

#include <thread>

using namespace System;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Threading;


HWND hwnd;
Handler* handler = nullptr;
Config* config = nullptr;
HANDLE hRecoil, hUpdate;

void recoilThread(); void updateThread();

#define __strcmp(a,b) (bool)(strcmp(a,b) == 0)

#define slot handler->slot
#define lastslot handler->lastSlot
#define stance handler->stance

void Main(array<String^>^ args)
{
	createDbgConsole();

	const char* computerHWID = getIdentifier();
	if (
		!__strcmp("b71acd838bac692a9640f0ed793f7441", computerHWID) &&	//desktop
		!__strcmp("5ad528ce2d9b88d3396cbfea97ef5029", computerHWID)		//laptop
		)
	{
#ifdef _DEBUG
		_D("hwid missmatch");
		_D(computerHWID);
		system("pause");
#endif
		return;
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	handler = new Handler();

	config = new Config();
	auto form = gcnew EscoCp::MyForm();
	form->setConfig(config);
	form->setHandler(handler);
	hwnd = form->getHwnd();
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

struct GlobalVariables
{
	bool recoil = false;
	int force = 0;
	int delay = 1;
} globals, locals;

void updateThread()
{
	bool g_doRecoil = false;
	int g_force;
	int g_delay;
	for (;;)
	{
		if (GetAsyncKeyState(VK_KEY_P))
		{
			ExitProcess(0);
		}
		bool l_doRecoil = true;
		if (!handler->mouse->at(VK_LBUTTON) ||
			!handler->mouse->at(VK_RBUTTON) ||
			slot == NOSLOT ||
			handler->profiles->at(slot) == nullptr) {
			l_doRecoil = false;
		}

		if (config->tabbedIn) {
			char string[32];
			GetWindowTextA(GetForegroundWindow(), string, sizeof(string));
			bool isInPubg = std::strstr(string, "TLEGR") != NULL;
			if (!isInPubg)
				l_doRecoil = false;
		}
		if (l_doRecoil) {
			Profile* profile = handler->profiles->at(slot);
			g_force = max(profile->recoil->at(stance), 0);
			g_delay = max(profile->delay->at(stance), 1);
		}


		g_doRecoil = l_doRecoil;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	return;
}


void recoilThread()
{
	_S("recoil thread started");
	for (;;)
	{
		if (handler->ingame && handler->mouse->at(VK_LBUTTON) && handler->mouse->at(VK_RBUTTON) && slot != NOSLOT && handler->profiles->at(slot) != nullptr)
		{
			int force, delay;
			do {
				force = max(handler->profiles->at(slot)->recoil->at(stance), 0);
				delay = max(handler->profiles->at(slot)->delay->at(stance), 1);
				input::move(0, force);
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			} while (handler->mouse->at(VK_LBUTTON) && slot != NOSLOT && handler->profiles->at(slot) != nullptr);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}

LRESULT CALLBACK kbProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (handler == NULL) {
		return NULL;
	}
	if (nCode < 0) {
		return CallNextHookEx(handler->kbHook,nCode,wParam,lParam);
	}

	LPKBDLLHOOKSTRUCT keyStruct = (LPKBDLLHOOKSTRUCT)lParam;

	if ((keyStruct->flags >> LLKHF_INJECTED) & 1) {
		// ignore injected events
	}
	else {
		DWORD key = keyStruct->vkCode;
		//insert if key not in map
		if (!handler->keyboard->count(key)) {
			handler->keyboard->insert({ key,false });
		}

		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			if (!handler->keyboard->at(key)) {
				handler->keyboard->at(key) = true;

				for (size_t i = 0; i < config->profileList->size(); i++) {
					Profile* profile = config->profileList->at(i);
					if (profile->onkey == key && slot != NOSLOT ) {
						handler->profiles->at(slot) = config->profileList->at(i);
						_D("SET " << profile->name << " to slot " << slot);
					}
				}
				if (key == config->vanishkey) {
					config->vanish = !config->vanish;
					ShowWindow(hwnd, config->vanish ? SW_HIDE : SW_SHOW);
					_D("SET gui " << (config->vanish ? "hidden" : "visible"));
				}

				//	Default actionkeys
				switch (key)
				{
				case VK_SPACE: {
					stance = STANDING;
					_D("SET stance " << stringifyStance( stance));
					break;
				}
				case VK_KEY_1: {
					slot = SLOT1;
					_D("SET slot 1");
					break;
				}
				case VK_KEY_2: {
					slot = SLOT2;
					_D("SET slot 2");
					break;
				}
				case VK_KEY_3:
				case VK_KEY_4: {
					slot = NOSLOT;
					_D("SET slot none");
					break;
				}
				//	Grenades
				case VK_KEY_J:
				case VK_KEY_H:
				case VK_KEY_G: {
					_D("SET slot none");
					slot = NOSLOT;
					lastslot = NOSLOT;
					break;
				}
				case VK_KEY_X: {
					if (slot == NOSLOT) {
						slot = lastslot;
					}
					else {
						lastslot = slot;
						slot = NOSLOT;
					}
					_D("SET slot " << slot);
					break;
				}
				case VK_KEY_C: {
					if (stance == STANDING || stance == PRONE) {
						stance = CROUCH;
					}
					else if (stance == CROUCH) {
						stance = STANDING;
					}
					_D("SET stance " << stringifyStance(stance));
					break;
				}
				case VK_KEY_Z: {
					if (stance == PRONE) {
						stance = STANDING;
					}
					else {
						stance = PRONE;
					}
					_D("SET stance " << stringifyStance(stance));
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
			handler->keyboard->at(key) = false;
			break;
		}
		default:
			break;
		}
		
	}
	return CallNextHookEx(handler->kbHook, nCode, wParam, lParam);
}

#define _D(x)

void kmMacro(DWORD key)
{
	if (key == config->vanishkey) {
		config->vanish = !config->vanish;
		ShowWindow(hwnd, config->vanish ? SW_HIDE : SW_SHOW);
		_D("SET gui " << (config->vanish ? "hidden" : "visible"));
	}
}


LRESULT CALLBACK moProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (handler == NULL) {
		return NULL;
	}
	if (nCode < 0) {
		return CallNextHookEx(handler->moHook, nCode, wParam, lParam);
	}

	LPMSLLHOOKSTRUCT mStruct = (LPMSLLHOOKSTRUCT)lParam;

	if ((mStruct->flags >> LLKHF_INJECTED) & 1) {
		//ignore injected
	}
	else {
#define keyDown(x) handler->mouse->at(x)

		switch (wParam)
		{
		case WM_LBUTTONDOWN: {
			if (!keyDown(VK_LBUTTON)) {
				keyDown(VK_LBUTTON) = true;
				_D("Left_");
			}

			break;
		}
		case WM_LBUTTONUP: {
			if (keyDown(VK_LBUTTON)) {
				keyDown(VK_LBUTTON) = false;
				_D("Left^");
			}

			break;
		}
		case WM_RBUTTONDOWN: {
			if (!keyDown(VK_RBUTTON)) {
				keyDown(VK_RBUTTON) = true;
				_D("Right_");
			}
			break;
		}
		case WM_RBUTTONUP: {
			if (keyDown(VK_RBUTTON)) {
				keyDown(VK_RBUTTON) = false;
				_D("Right^");
			}
			break;
		}
		case WM_XBUTTONDOWN: {
			int ind = GET_XBUTTON_WPARAM(mStruct->mouseData);

			if (ind == 1) {
				if (!keyDown(VK_XBUTTON1)) {
					keyDown(VK_XBUTTON1) = true;
					_D("x1_");
					kmMacro(VK_XBUTTON1);
				}
			}else if (ind == 2) {
				if (!keyDown(VK_XBUTTON2)) {
					keyDown(VK_XBUTTON2) = true;
					_D("x2_");
					kmMacro(VK_XBUTTON2);
				}
			}
			break;
		}
		case WM_XBUTTONUP: {
			int ind = GET_XBUTTON_WPARAM(mStruct->mouseData);

			if (ind == 1) {
				if (keyDown(VK_XBUTTON1)) {
					keyDown(VK_XBUTTON1) = false;
					_D("x1^");
				}
			}
			else if (ind == 2) {
				if (keyDown(VK_XBUTTON2)) {
					keyDown(VK_XBUTTON2) = false;
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
			if (!keyDown(VK_MBUTTON)) {
				keyDown(VK_MBUTTON) = true;
				_D("Middle_");
				kmMacro(VK_MBUTTON);
			}
			break;
		}
		case WM_MBUTTONUP: {
			if (keyDown(VK_MBUTTON)) {
				keyDown(VK_MBUTTON) = false;
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
	return CallNextHookEx(handler->moHook, nCode, wParam, lParam);
}