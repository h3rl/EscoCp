#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#ifdef _DEBUG

#define _D(x) std::cout << x << std::endl;
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