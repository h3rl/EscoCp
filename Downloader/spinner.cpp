#include "spinner.h"

#pragma once

#include <iostream>
#include <Windows.h>

using namespace std;


/*
*   Spinner Class function definitions
*
*/

void Spinner::update()
{
    printf_s("\r%s %c", msg.c_str(), spinner[cnt]);

    cnt++;
    if (cnt >= strlen(spinner))
    {
        cnt = 0;
    }
}
Spinner::Spinner(const char* message)
{
    msg = message;
}

Spinner::~Spinner()
{
    if (this->bFailed) {
        printf_s("\r%s  \n", msg.c_str());
    }
    else {
        printf_s("\r%s Ok\n", msg.c_str());
    }
}


/*
*   Progressbar Class function definitions
*
*/

void Progressbar::update(float val)
{
    if (!running)
        return;
    if (value == val || !maxvalue)
        return;
    value = val;

    float percent = val / maxvalue;

    int printbars = (int)min(barlength, roundf(barlength * percent));

    string ret = "[";
    for (int i = 0; i < barlength; i++)
    {
        if (printbars > 0) {
            ret += "=";
            printbars--;
        }
        else
        {
            ret += " ";
        }
    }
    ret += "]";

    percent = min(100, percent * 100);

    printf("\r%s %s %.*f%%", msg.c_str(), ret.c_str(), 1, percent);

    if (percent == 100.f) {
        printf("\n");
        running = false;
    }
}
void Progressbar::setMax(float max)
{
    maxvalue = max;
}

Progressbar::Progressbar(const char* message)
{
    running = true;
    msg = message;
}