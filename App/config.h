#pragma once
#include "nlohmann/json.hpp"

#pragma comment (lib, "User32.lib")//fixed showwindow functions

#include <Windows.h>


using json = nlohmann::json;


/*
*  Profile - one profile per recoilprofile.
*/

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

/*
*  Config - class that the config file is read to.
*/

class Config {
public:
    std::vector<Profile> profileList;
    int vanishkey;
    bool vanish;
    bool onTop;
    bool tabbedIn;
    int x, y;
public:
    Config() {
        tabbedIn = true;
        onTop = false;
        vanish = false;
    };
    ~Config() {};
    bool read();
    void create();
    bool write();
};