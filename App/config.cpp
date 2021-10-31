#include "config.h"
#include "debug.h"
#include "convert.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <Winuser.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Threading;
using namespace System::Drawing;

#define CFGNAME "config.cfg"

Profile::Profile() {
    this->name = "";
    this->onkey = -1;
    this->delay->clear();
    for (size_t i = 0; i < 3; i++)
        this->delay->push_back(1);

    this->recoil->clear();
    for (size_t i = 0; i < 3; i++)
        this->recoil->push_back(0);
}

bool Config::read() {
    // empty profile list
    profileList->clear();
    // read JSON file
    std::ifstream i(CFGNAME);

    //check if file exists
    if (i.good()) {

        std::string lastread;
        json j;
        try {
            //  parse file contents to json object
            i >> j;

            //  we are done reading file, close it
            i.close();
        }
        catch (std::exception e)
        {
            if (i) i.close();

            _D(e.what());

            // Initializes the variables to pass to the MessageBox.Show method.
            String^ message = "Config is not in \"json\" format...\nCheck for typos. You can also delete cfg to create a new one\n\n" + String(e.what()).ToString();
            String^ caption("Parsing Config FAILED");

            MessageBox::Show(message, caption, MessageBoxButtons::OK, MessageBoxIcon::Error);
            ExitProcess(0);
            return false;
        }
        
        //  Now read the config since it is in json format. 
        //  log last read location so we can tell user where the error is.
        try {
            lastread = "onTop";
            onTop = j["onTop"].get<bool>();

            lastread = "tabbedIn";
            tabbedIn = j["tabbedIn"].get<bool>();

            lastread = "vanishkey";
            vanishkey = j["vanishkey"].get<int>();

            lastread = "window -> x";
            x = j["window"]["x"].get<int>();

            lastread = "window -> y";
            y = j["window"]["y"].get<int>();

            lastread = "profiles";
            if (!j.contains("profiles"))
                throw std::exception("");

            const size_t profilessize = j["profiles"].size();
            //  now read each profile
            for (size_t i = 0; i < profilessize; i++)
            {
                auto jprofile = &j["profiles"].at(i);
                Profile* profile = new Profile();

                lastread = "profiles/" + std::to_string(i) + "/name";
                profile->name = jprofile->at("name").get<std::string>();

                lastread = "profiles/" + std::to_string(i) + "/onkey";
                profile->onkey = jprofile->at("onkey").get<int>();

                lastread = "profiles/" + std::to_string(i) + "/recoil";
                if (!jprofile->contains("recoil"))
                    throw std::exception("");

                size_t recoilLength = jprofile->at("recoil").size();
                profile->recoil->clear();
                for (size_t r = 0; r < recoilLength; r++)
                {
                    int val = jprofile->at("recoil").at(r).get<int>();
                    profile->recoil->push_back(val);
                }
                if (profile->recoil->size() != 3) {
                    throw std::exception("size is supposed to be 3");
                }

                lastread = "profiles/" + std::to_string(i) + "/delay";
                if (!jprofile->contains("delay"))
                    throw std::exception("");

                size_t delayLength = jprofile->at("delay").size();

                profile->delay->clear();
                for (size_t d = 0; d < delayLength; d++)
                {
                    int val = jprofile->at("delay").at(d).get<int>();
                    profile->delay->push_back(val);
                }

                if (profile->delay->size() != 3) {
                    throw std::exception("size is supposed to be 3");
                }

                profileList->push_back(profile);
            }

            _S("Read Config");
        }
        catch (std::exception e)
        {
            //  got some error while parsing json,
            //  now we give some feedback about where the error occured.
            _E(e.what());
            String^ message = String(lastread.c_str()).ToString() + " is undefined\ndefine it or delete config to make a new one\n\n" + String(e.what()).ToString();
            String^ caption("Parsing Config FAILED");

            MessageBox::Show(message, caption, MessageBoxButtons::OK, MessageBoxIcon::Error);
            ExitProcess(0);
            return false;
        }

        return true;
    }
    else {
        //  file does not exist, so we create one.
        create();
        //  then we read the created config.
        return read();
    }
}

bool Config::write() {
    std::ofstream o(CFGNAME);
    json k;
    k["onTop"] = onTop;
    k["tabbedIn"] = tabbedIn;
    k["vanishkey"] = vanishkey;
    k["window"]["x"] = x;
    k["window"]["y"] = y;
    for (size_t i = 0; i < profileList->size(); i++) {
        auto profile = profileList->at(i);
        k["profiles"].push_back(json::object());
        k["profiles"][i]["name"] = profile->name;
        k["profiles"][i]["onkey"] = profile->onkey;
        k["profiles"][i]["recoil"] = *profile->recoil;
        k["profiles"][i]["delay"] = *profile->delay;
    }
    o << std::setw(2) << k << std::endl;
    o.close();
    return true;
}

void Config::create() {
    json k;
    k["onTop"] = true;
    k["tabbedIn"] = false;
    k["window"]["x"] = 100;
    k["window"]["y"] = 100;
    k["vanishkey"] = -1;

    auto testprofiles = new std::vector<Profile*>();
    Profile* profile = new Profile();
    profile->name = "Passive";
    profile->onkey = 117;
    profile->recoil = new std::vector<int>{ 0, 0, 0 };
    profile->delay = new std::vector<int>{ 5, 5, 5 };
    testprofiles->push_back(profile);

    profile = new Profile();
    profile->name = "Light";
    profile->onkey = 118;
    profile->recoil = new std::vector<int>{ 5, 4, 3 };
    profile->delay = new std::vector<int>{ 5, 5, 5 };
    testprofiles->push_back(profile);

    profile = new Profile();
    profile->name = "Heavy";
    profile->onkey = 119;
    profile->recoil = new std::vector<int>{ 11, 9, 7 };
    profile->delay = new std::vector<int>{ 4, 4, 4 };
    testprofiles->push_back(profile);

    for (size_t i = 0; i < testprofiles->size(); i++) {
        k["profiles"].push_back(json::object());
        k["profiles"][i]["name"] = testprofiles->at(i)->name;
        k["profiles"][i]["onkey"] = testprofiles->at(i)->onkey;
        k["profiles"][i]["recoil"] = *testprofiles->at(i)->recoil;
        k["profiles"][i]["delay"] = *testprofiles->at(i)->delay;
    }

    std::ofstream o(CFGNAME);
    if(o){
        o << std::setw(2) << k << std::endl;
        o.close();
        _S(std::string(CFGNAME)+" created");
    }
    else {
        _E("failed to create "+std::string(CFGNAME));
        String^ message = "failed to create "+ String(CFGNAME).ToString()+"\n\ntry running as administrator";
        String^ caption("Config creation failed");

        Windows::Forms::DialogResult res = MessageBox::Show(message, caption, MessageBoxButtons::OK, MessageBoxIcon::Error);
        ExitProcess(0);
    }
}