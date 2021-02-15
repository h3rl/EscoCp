#pragma once
#include "nlohmann/json.hpp"

#pragma comment (lib, "User32.lib")//fixed showwindow functions

#include <Windows.h>


using json = nlohmann::json;

class Profile
{
public:
    Profile();
    ~Profile(){};
    std::string name;
    int onkey;
    std::vector<int> recoil;
    std::vector<int> delay;
};

class Config {
public:
    std::vector<Profile> profileList;
    bool hidden;
    bool onTop;
    int x, y;
public:
    Config() {
        onTop = false;
        hidden = false;
    };
    ~Config() {};
    bool read();
    void create();
    bool write();
};