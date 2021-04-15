#pragma once

#ifndef _DEBUGLIB_INITIALIZED
#define _DEBUGLIB_INITIALIZED

#include <iostream>
#include <windows.h>
#include <string>

#ifdef _DEBUG

HANDLE hConsole;
#define _D(x) std::cout << x << std::endl;
#define STRING(x) #x

#else

#define _D(x)
#define STRING(x)

#endif // _DEBUG



void createDbgConsole() {
#ifdef _DEBUG
    SetConsoleTitleA("Debugging Console");
    if (!AllocConsole()) {
        // Add some error handling here.
        // You can call GetLastError() to get more info about the error.
        return;
    }

    // std::cout, std::clog, std::cerr, std::cin
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#endif
}

void _S(const char* txt) {
#ifdef _DEBUG
    SetConsoleTextAttribute(hConsole, 10);
    _D("[OK] - " << txt);
    SetConsoleTextAttribute(hConsole, 15);
#endif
}

void _S(std::string txt) {
#ifdef _DEBUG
    _S(txt.c_str());
#endif
}

void _E(const char* txt) {
#ifdef _DEBUG
    SetConsoleTextAttribute(hConsole, 12);
    _D("[ERR] - " << txt);
    SetConsoleTextAttribute(hConsole, 15);
#endif
}

void _E(std::string txt) {
#ifdef _DEBUG
    _E(txt.c_str());
#endif
}

class exp : std::exception
{
private:
    int code;
public:
    exp()
    {
        this->code = GetLastError();
    }
public:
    void handle()
    {
        std::string msg(this->what());
        msg.append("\n err:" + std::to_string(this->code));

        MessageBoxA(NULL, msg.c_str(), "exeption", MB_ICONERROR | MB_OK);
        ExitProcess(GetLastError());
    }
};


#endif // !_DEBUGLIB_INITIALIZED