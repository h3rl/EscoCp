#include "CCallback.h"
#include "debug.h"
#include "network.h"
#include "util.h"
#include "md5file.h"


#include <WinInet.h>
#include <WinInet.h>


#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")

string message;

const char* filename = "100MB-atlanta.bin";

bool versionChecked = false;
bool versionMatch = false;

Spinner* spinner = nullptr;
Progressbar* progressbar = nullptr;

void workerThread()
{
    try
    {
        string currenthash = toUpper(getFileHash(filename));

        const char* url = "https://h3rl-firstapp.web.app/hash";
        string netHash = getDataFromUrl(url);

        versionMatch = currenthash.compare(netHash) == 0;

        versionChecked = true;
        return;
    }
    catch (const std::exception& exp)
    {
        spinner->failed();
        _D(exp.what() << " err: " << GetLastError());
        delete &exp;
    }
}

int main()
{
    SetConsoleTitleA("EscoLoader v1.0");
    spinner = new Spinner("Checking versions");
    HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)workerThread, 0, 0, 0);
    while (!versionChecked)
    {
        spinner->update();
        Sleep(100);
    }
    if (!versionMatch) {
        spinner->failed();
        printf("Not up to date, downloading latest...\n");
        string dir = GetCurrentDir() + "\\" + filename;

        CCallback callback; // used to set the progress bar

        //DeleteUrlCacheEntryW(TEXT("https://h3rl.com/esco.txt"));//Clear the cache
        //HRESULT hr = URLDownloadToFileA(NULL, "https://h3rl.com/esco.txt", dir.c_str(), 0, (LPBINDSTATUSCALLBACK)&callback);
        try {
            DeleteUrlCacheEntryA("http://speedtest.atlanta.linode.com/100MB-atlanta.bin");//Clear the cache
        }
        catch (...) {

        }
        HRESULT hr = URLDownloadToFileA(NULL, "http://speedtest.atlanta.linode.com/100MB-atlanta.bin",
            dir.c_str(), 0, (LPBINDSTATUSCALLBACK)&callback);
        if (FAILED(hr)) {
            printf("URLDownloadToFile failed: %d\n", GetLastError());
            system("pause");
            ExitProcess(0);
        }
    }
    else {
        spinner->success();
        printf("Up to date..\n");
    }
    printf("\n\n");
    system("pause");
}

