#include <iostream>
#include <windows.h>

using namespace std;


int main()
{
    char chars[32]; // [rsp+E8h] [rbp-20h] BYREF
    char buffer[96]; // [rsp+108h] [rbp+0h] BYREF

    strcpy_s(chars, "abcdefghijklmnopqrstuvwxyz");
    for (int i = 0; i <= 80; ++i)
        buffer[i] = chars[rand() % 26];
    buffer[80] = 0;

    cout << buffer << endl;
}