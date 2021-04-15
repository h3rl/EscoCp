#pragma once

#include <debug.hpp>

#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>

#include <fstream>

#define BUFSIZE 1024
#define MD5LEN  16

const char* getFileHash(const char* filename)
{

    size_t s = sizeof(char) * 64;

    char* buff = (char*)malloc(s);


    string hashresult = "";
    DWORD dwStatus = 0;
    BOOL bResult = FALSE;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile = NULL;
    BYTE rgbFile[BUFSIZE];
    DWORD cbRead = 0;
    DWORD totRead = 0;
    BYTE rgbHash[MD5LEN];
    DWORD cbHash = 0;
    CHAR rgbDigits[] = "0123456789abcdef";
    //LPCWSTR filename = L"esco.txt";
    // Logic to check usage goes here.

    ifstream file(filename, ios::binary | ios::ate);
    int filesize = (int)file.tellg();
    file.close();

    std::ifstream i(filename,ios::binary);


    if (!i.good())
    {
        i.close();
        /*
        dwStatus = GetLastError();
        printf("Error opening file %s\nError: %d\n", filename, dwStatus);
        */
        return "nofile";
    }

    // Get handle to the crypto provider
    if (!CryptAcquireContextA(&hProv,
        NULL,
        NULL,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT))
    {
        dwStatus = GetLastError();
        printf("CryptAcquireContext failed: %d\n", dwStatus);
        return "";
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        dwStatus = GetLastError();
        printf("CryptAcquireContext failed: %d\n", dwStatus);
        CryptReleaseContext(hProv, 0);
        return "";
    }



    while(true) {

        int delta = filesize - totRead;

        if (delta < BUFSIZE) {
            i.read((char*)rgbFile, delta);
        }
        else {
            i.read((char*)rgbFile, BUFSIZE);
        }

        cbRead = (DWORD)i.gcount();
        totRead += cbRead;

        //_D("filesize: " << filesize);
        //_D("cbread: " << cbRead);
        if (cbRead == 0) {
            break;
        }

        if (!CryptHashData(hHash, rgbFile, cbRead, 0))
        {
            dwStatus = GetLastError();
            printf("CryptHashData failed: %d\n", dwStatus);
            CryptReleaseContext(hProv, 0);
            CryptDestroyHash(hHash);
            return "";
        }
    }

    cbHash = MD5LEN;
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
    {
        for (DWORD i = 0; i < cbHash; i++)
        {
            sprintf_s(&buff[i*2],s, "%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
            //printf_s("%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
        }
    }
    else
    {
        dwStatus = GetLastError();
        printf("CryptGetHashParam failed: %d\n", dwStatus);
    }

    return buff;
}