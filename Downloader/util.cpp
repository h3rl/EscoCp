#include "util.h"

#include <Windows.h>

std::string toUpper(std::string str) {
    std::string loc = "";
    for (std::string::size_type i = 0; i < str.length(); ++i)
        loc += std::toupper(str[i]);
    return loc;
}

std::string GetCurrentDir()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos);
}