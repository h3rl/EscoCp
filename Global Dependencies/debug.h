#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#pragma comment(lib,"User32.lib")

#define _M(x) std::cout << x << std::endl;

#ifdef _DEBUG

#define _D(x) _M(x)
#define STRING(x) #x

#else

#define _D(x)
#define STRING(x)

#endif // _DEBUG

void createDbgConsole();

void _S(const char* txt);

void _S(std::string txt);

void _E(const char* txt);

void _E(std::string txt);

void _DARR(std::vector<std::string> &arr);

class exp : std::exception
{
private:
    int code;
public:
    exp();
public:
    void handle();
};