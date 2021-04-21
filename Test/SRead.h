#pragma once

#include <iostream>
#include <string>

using namespace std;

class SRead
{
private:

    string pson;
    int i = 0;
    char* c = 0;

public:

    SRead(string str) {
        if (str.size() != 0) {
            pson = str;
            parse();
        }
    }
    ~SRead() {

    }


private:

    void parse()
    {

    }

    void parseObject() {
    }

    void nextLetter() {
        i++;
        c = &pson.at(i);
    }
};