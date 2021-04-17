#pragma once

#include "header.h"
#include "debug.h"
#include "config.h"

#include <map>
#include <vector>
#include <Windows.h>


//	callbacks for windowshooks that capture keyboard and mouse events.
LRESULT CALLBACK kbProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK moProc(int nCode, WPARAM wParam, LPARAM lParam);


/*
*	Handler - class for handeling kb and mo input.
*/
class Handler
{
public:
	std::vector<Profile*> profiles = { nullptr,nullptr };

	HHOOK kbHook;
	HHOOK moHook;
	HANDLE htMessage;
	std::map<DWORD, bool>* kbKeys = new std::map<DWORD, bool>;
	std::map<DWORD, bool>* moKeys = new std::map<DWORD, bool>{
		{ VK_MBUTTON,false },
		{ VK_LBUTTON,false },
		{ VK_RBUTTON,false },
		{ VK_XBUTTON1,false },
		{ VK_XBUTTON2,false }
	};

public:

	bool ingame;
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