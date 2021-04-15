#pragma once
#include <iostream>
#include <windows.h>

#include <string>

#ifdef _DEBUG

#define _D(x) std::cout << x << std::endl;
#define STRING(x) #x

#else

#define _D(x)
#define STRING(x)

#endif // _DEBUG

#ifdef DEBUG_EXTRA_INFO

#define _P(x) _D(x) 

#else

#define _P(x)

#endif // DEBUG_EXTRA_INFO


void createDbgConsole();
void _S(const char* txt);
void _S(std::string txt);
void _E(const char* txt);
void _E(std::string txt);

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
        msg.append("\n err:"+std::to_string(this->code));

        MessageBoxA(NULL, msg.c_str(), "exeption", MB_ICONERROR | MB_OK);
        ExitProcess(GetLastError());
    }
};