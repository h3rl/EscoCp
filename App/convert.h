#pragma once
#include <msclr\marshal_cppstd.h>
#include "header.h"
#include <string>

std::string sysToStd(System::String^ txt);
const char* sysToCstr(System::String^ txt);

std::string ws2s(const std::wstring& wstr);
std::wstring s2ws(const std::string& str);

#define caseStringify(x) case x: return std::string(#x).erase(0,3);
std::string vkToString(int vk);

const char* stringifyStance(Stance stance);
const char* stringifySlot(Slot slot);
