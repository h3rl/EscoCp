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
    std::string activateKeyName;
    DWORD activateKey;
    std::vector<int> recoil;
    std::vector<int> delay;

    void setDefault();
};

class Config {
public:
    std::vector<Profile> profileList;
    bool hidden;
    bool onTop;
    int x, y;
    json j;
public:
    Config() {
        onTop = false;
        hidden = false;
    };
    ~Config() {};
    bool readConfigFile();
    void create();
};