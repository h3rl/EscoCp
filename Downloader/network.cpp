#include "network.h"
#include "debug.h"

#include <Windows.h>
#include <WinInet.h>


#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")


const char* getDataFromUrl(const char* url) {

    HINTERNET hOpen = NULL;
    HINTERNET hFile = NULL;
    DWORD dwBytesRead = 0;

    hOpen = InternetOpenA("Agents", NULL, NULL, NULL, NULL);
    if (!hOpen) {
        throw "InternetOpenA failed";
    }
    hFile = InternetOpenUrlA(hOpen, url, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, NULL);
    if (!hFile) {
        InternetCloseHandle(hOpen);
        throw std::exception("InternetOpenUrlA failed");
    }

    size_t s = sizeof(char) * 32;

    char* buffer = (char*)malloc(s);
    char* outbuffer = (char*)malloc(s);

    if (!buffer || !outbuffer)
    {
        free(buffer);
        free(outbuffer);
        throw "bufferallocation failed";
    }

    BOOL read = InternetReadFile(hFile, (void*)buffer, s, &dwBytesRead);

    InternetCloseHandle(hFile);
    InternetCloseHandle(hOpen);

    if (!read)
    {
        free(buffer);
        free(outbuffer);
        throw "InternetReadFile failed";
    }

    for (size_t i = 0; i < dwBytesRead; i++)
    {
        sprintf_s(&outbuffer[i], s, "%c", buffer[i]);

    }

    free(buffer);

    return outbuffer;

}