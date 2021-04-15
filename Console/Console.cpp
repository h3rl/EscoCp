// EscoIdentifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Escolib.h"


#pragma comment(lib,"Library.lib")

#include <iostream>
#include <Windows.h>

//
/*
    04/03/2021 1318

drive: 927817347
gpu: 85A010431B81
mboard: K717166573
cname: H3RLANDSEN
net: 1C872CB76B5A2CF05D79B1C8
cpu: 372647222

prehwid: 85A010431B81372647222K717166573H3RLANDSEN1C872CB76B5A2CF05D79B1C8927817347
hwid: a0c6128e1fb4a5de6dcf420abc791fec
*/


using namespace std;



extern "C" ESCOLIBRARY_API const char* getIdentifier();

int main()
{
    SetConsoleTitle(L"EscoIdentifier");
    printf("hwid: %s\n\n", getIdentifier());
    system("pause");
    return EXIT_SUCCESS;
}