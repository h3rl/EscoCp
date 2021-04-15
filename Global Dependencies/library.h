// Escolib.h - Contains declarations of hwid functions
#pragma once

#ifdef ESCOLIBRARY_EXPORTS
#define ESCOLIBRARY_API __declspec(dllexport)
#else
#define ESCOLIBRARY_API __declspec(dllimport)

#pragma comment(lib,"Library.lib")
extern "C" __declspec(dllimport) const char* getIdentifier();
#endif

