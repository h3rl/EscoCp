// Escolib.h - Contains declarations of hwid functions
#pragma once

#define ESCOLIBRARY_API __declspec(dllimport)
#pragma comment(lib,"Library.lib")
extern "C" ESCOLIBRARY_API const char* getIdentifier();

