#pragma once

#include <iostream>
#include <Windows.h>

using namespace std;

class Spinner
{
private:
    size_t cnt = 0;
    const char* spinner = "|/-\\";

public:
    string msg;

    Spinner(const char* message);
    ~Spinner();

    void update();
};

class Progressbar
{
private:
    float maxvalue;
    float value;
    const int barlength = 20;
public:
    bool running;
    string msg;

    Progressbar(const char* message);

    void update(float val);
    void setMax(float max);
};