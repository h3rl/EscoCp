// Escolib.h - Contains declarations of hwid functions
#pragma once

#define ESCOLIBRARY_EXPORTS

#ifdef ESCOLIBRARY_EXPORTS
#define ESCOLIBRARY_API __declspec(dllexport)
#else
#define ESCOLIBRARY_API __declspec(dllimport)
#endif