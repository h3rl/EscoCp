#pragma once

#include "header.h"
#include "debug.h"
#include "config.h"

#include <map>
#include <vector>
#include <Windows.h>

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

class Handler
{
public:
	std::vector<Profile*> profiles = { nullptr,nullptr };

	HHOOK m_hHook;
	HANDLE m_hMessage;
	std::map<DWORD, bool>* m_pKeys = new std::map<DWORD, bool>;
public:

	bool m_bCaptureKey;
	Stance stance;
	Slot slot, lastSlot;

	struct Status
	{
		bool visible{ true };
		bool reloadcfg{ false };
	} status;

	Handler();
	~Handler();

	static void messageThread();
};