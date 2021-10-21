//	librarydefs.h - includes definitions for export and import
#pragma once

#define ESCOLIB_IMPORT extern "C" __declspec(dllimport)
#define ESCOLIB_EXPORT extern "C" __declspec(dllexport)
