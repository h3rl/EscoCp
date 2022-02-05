#include <library.h>

#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>


using namespace std;

std::wstring s2ws(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 350, 300, TRUE); // 800 width, 100 height
    SetConsoleTitleA("Esco Identifier");
    _setmode(_fileno(stdout), _O_U16TEXT);

    wprintf(L"\n");
    wprintf(L"  ▓█████   ██████  ▄████▄   ▒█████  \n");
    wprintf(L"  ▓█   ▀ ▒██    ▒ ▒██▀ ▀█  ▒██▒  ██▒\n");
    wprintf(L"  ▒███   ░ ▓██▄   ▒▓█    ▄ ▒██░  ██▒\n");
    wprintf(L"  ▒▓█  ▄   ▒   ██▒▒▓▓▄ ▄██▒▒██   ██░\n");
    wprintf(L"  ░▒████▒▒██████▒▒▒ ▓███▀ ░░ ████▓▒░\n");
    wprintf(L"  ░░ ▒░ ░▒ ▒▓▒ ▒ ░░ ░▒ ▒  ░░ ▒░▒░▒░ \n");
    wprintf(L"   ░ ░  ░░ ░▒  ░ ░  ░  ▒     ░ ▒ ▒░ \n");
    wprintf(L"     ░   ░  ░  ░  ░        ░ ░ ░ ▒  \n");
    wprintf(L"     ░  ░      ░  ░ ░          ░ ░  \n");
    wprintf(L"                  ░                 \n");

    const char* raw_hwid = getIdentifier();
    wstring hwid = s2ws(raw_hwid);
    size_t size = strlen(raw_hwid);

    wprintf(L"hwid: %s\n", hwid.c_str());


    auto glob = GlobalAlloc(GMEM_FIXED, size+1);
    if (glob) {
        memcpy(glob, raw_hwid, size);

        OpenClipboard(GetConsoleWindow());
        EmptyClipboard();
        SetClipboardData(CF_TEXT, glob);
        CloseClipboard();
        wprintf(L"copied to clipboard!\n");
    }
    wprintf(L"\n");
    system("pause");
    return EXIT_SUCCESS;
}

