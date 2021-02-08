#pragma once

#include "header.h"
#include "debug.h"

#include <map>
#include <Windows.h>

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

class Handler
{
public:
	HHOOK m_hHook;
	HANDLE m_handle;
	std::map<int, bool>* m_pKeys = new std::map<int, bool>;
public:

	bool m_bCaptureKey;
	LPARAM m_clParam;
	Stance stance;
	Slot slot, lastSlot;

	struct Status
	{
		bool visible{ true };
		bool reloadcfg{ false };
	} status;

	Handler();
	~Handler();

	static void handlerThread();
};