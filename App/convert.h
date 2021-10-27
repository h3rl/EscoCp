#pragma once
#include <msclr\marshal_cppstd.h>
#include "header.h"
#include <string>

std::string sysToStd(System::String^ txt);
const char* sysToCstr(System::String^ txt);

#define caseStringify(x) case x: return std::string(#x).erase(0,3);
std::string vkToString(int vk);

const char* stringifyStance(Stance stance);
const char* stringifySlot(Slot slot);
