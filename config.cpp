#include "config.h"
#include "debug.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <Winuser.h>

Profile::Profile() {
    this->name = "";
    this->activateKeyName = "";
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
    std::ifstream i("config.json");
    if (i) {
        i >> j;
        try {
            onTop = j["onTop"].get<bool>();
            x = j["window"]["x"].get<int>();
            y = j["window"]["y"].get<int>();
            auto profileLength = j["profiles"].size();
            for (size_t i = 0; i < profileLength; i++)
            {
                Profile profile = Profile();

                profile.name = j["profiles"][i]["name"].get<std::string>();
                //profile.activateKey = j["profiles"][i]["activate"].get<DWORD>();

                size_t recoilLength = j["profiles"][i]["recoil"].size();
                for (size_t r = 0; r < recoilLength; r++)
                {
                    int val = j["profiles"][i]["recoil"][r].get<int>();
                    profile.recoil.push_back(val);
                }

                size_t delayLength = j["profiles"][i]["delay"].size();
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
            i.close();
            _E("Failed to read config.json, check for typos");
            _E("You can also delete it to make a new one");
            return false;
        }
        _S("Read Config");
        i.close();
        return true;
    }
    create();
    return false;
}

void Config::create() {
    std::ofstream o("config.json");
    if (o) {
        o << "{" << std::endl;
        o << "  \"onTop\": true," << std::endl;
        o << "  \"window\": {" << std::endl;
        o << "    \"x\": -300," << std::endl;
        o << "    \"y\": 360" << std::endl;
        o << "  }," << std::endl;
        o << "  \"table\": [" << std::endl;
        o << "    {" << std::endl;
        o << "      \"name\": \"Light\"," << std::endl;
        o << "      \"activate\": \"F21\"," << std::endl;
        o << "      \"recoil\": [ 7, 6, 5 ]," << std::endl;
        o << "      \"delay\": [ 10, 10, 10 ]" << std::endl;
        o << "    }," << std::endl;
        o << "    {" << std::endl;
        o << "      \"name\": \"Heavy\"," << std::endl;
        o << "      \"activate\": \"F22\"," << std::endl;
        o << "      \"recoil\": [ 9, 8, 7 ]," << std::endl;
        o << "      \"delay\": [12, 11, 11] " << std::endl;
        o << "    }" << std::endl;
        o << "  ]" << std::endl;
        o << "}" << std::endl;
        o.close();
        _S("config.json created");
    }
    else {
        _E("failed to create config.json");
    }
}