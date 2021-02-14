#include "config.h"
#include "debug.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <Winuser.h>

#define CFGNAME "config_test.json"

Profile::Profile() {
    this->name = "";
    this->onkey = -1;
    this->delay.clear();
    for (size_t i = 0; i < 3; i++)
        this->delay.push_back(1);

    this->recoil.clear();
    for (size_t i = 0; i < 3; i++)
        this->recoil.push_back(0);
}

bool Config::readConfigFile() {
    // empty profile list
    profileList.clear();
    // read JSON file
    std::ifstream i(CFGNAME);
    if (i) {
        std::string lastread;
        json j;
        i >> j;
        try {
            lastread = "onTop";
            onTop = j["onTop"].get<bool>();

            lastread = "x";
            x = j["window"]["x"].get<int>();

            lastread = "y";
            y = j["window"]["y"].get<int>();

            auto profileLength = j["profiles"].size();
            for (size_t i = 0; i < profileLength; i++)
            {
                Profile profile = Profile();

                lastread = std::to_string(i) + " name";
                profile.name = j["profiles"][i]["name"].get<std::string>();
                
                lastread = std::to_string(i) + " onkey";
                profile.onkey = j["profiles"][i]["onkey"].get<int>();
                
                lastread = std::to_string(i) + " recoil";
                size_t recoilLength = j["profiles"][i]["recoil"].size();
                
                profile.recoil.clear();
                for (size_t r = 0; r < recoilLength; r++)
                {
                    int val = j["profiles"][i]["recoil"][r].get<int>();
                    profile.recoil.push_back(val);
                }

                lastread = std::to_string(i) + " delay";
                size_t delayLength = j["profiles"][i]["delay"].size();

                profile.delay.clear();
                for (size_t d = 0; d < recoilLength; d++)
                {
                    int val = j["profiles"][i]["delay"][d].get<int>();
                    profile.delay.push_back(val);
                }

                profileList.push_back(profile);
            }
        }
        catch (...)
        {
            if (j) {
                j.clear();
            }
            i.close();
            _E("Failed to read config, check for typos");
            _E("You can also delete it to make a new one");
            _D("last read: " << lastread);
            return false;
        }
        _S("Read Config");
        j.clear();
        i.close();
        return true;
    }
    create();
    return false;
}

bool Config::write() {
    std::ofstream o(CFGNAME);
    json k;
    k["onTop"] = onTop;
    k["window"]["x"] = x;
    k["window"]["y"] = y;
    for (size_t i = 0; i < profileList.size(); i++) {
        k["profiles"].push_back(json::object());
        k["profiles"][i]["name"] = profileList.at(i).name;
        k["profiles"][i]["onkey"] = profileList.at(i).onkey;
        k["profiles"][i]["recoil"] = profileList.at(i).recoil;
        k["profiles"][i]["delay"] = profileList.at(i).delay;
    }
    o << std::setw(2) << k << std::endl;
    o.close();
    return true;
}

void Config::create() {
    json k;
    k["onTop"] = true;
    k["window"]["x"] = 100;
    k["window"]["y"] = 100;

    std::vector<Profile> testprofs = { Profile(), Profile() };
    testprofs.at(0).name = "first profile";
    testprofs.at(0).onkey = 118;
    testprofs.at(0).recoil = { 5, 4, 3 };
    testprofs.at(0).delay = { 5, 5, 5 };

    testprofs.at(1).name = "second profile";
    testprofs.at(1).onkey = 119;
    testprofs.at(1).recoil = { 11, 9, 7 };
    testprofs.at(1).delay = { 4, 4, 4 };

    for (size_t i = 0; i < testprofs.size(); i++) {
        k["profiles"].push_back(json::object());
        k["profiles"][i]["name"] = testprofs.at(i).name;
        k["profiles"][i]["onkey"] = testprofs.at(i).onkey;
        k["profiles"][i]["recoil"] = testprofs.at(i).recoil;
        k["profiles"][i]["delay"] = testprofs.at(i).delay;
    }

    std::ofstream o(CFGNAME);
    if(o){
        o << std::setw(2) << k << std::endl;
        o.close();
        _S("config.json created");
    }
    else {
        _E("failed to create config");
    }
}