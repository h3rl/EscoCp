// EscoIdentifier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <library.h>

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

int main()
{
    SetConsoleTitleA("EscoIdentifier");
    const char* hwid = getIdentifier();
    size_t size = strlen(hwid);

    printf("hwid: %s\n", hwid);

    auto glob = GlobalAlloc(GMEM_FIXED, size+1);
    if (glob) {
        memcpy(glob, hwid, size);

        OpenClipboard(GetConsoleWindow());
        EmptyClipboard();
        SetClipboardData(CF_TEXT, glob);
        CloseClipboard();
        printf("copied to clipboard!\n");
    }
    printf("\n\n");
    system("pause");
    return EXIT_SUCCESS;
}