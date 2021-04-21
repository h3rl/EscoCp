#include "debug.h"

#include <Windows.h>
#include <iostream>
#include <fstream>

#include <string>
#include <map>
#include <vector>

using namespace std;

struct KeyObj {
    string key{ "" };
    int vk{ -1 };
    bool bShift{ false };
    bool bCtrl{ false };
};


class Parser
{
public:
    string content;
    ifstream ifs;

    enum oType {
        NONE,
        STRING,
        NUMBER,
        OBJECT,
        ARRAY
    };

    Parser(const char* file)
    {
        if (!this->read(file))
        {
            _E("error reading file");
            return;
        }
        else {
            _S("read the file");
        }
    }

    ~Parser()
    {
        this->ifs.close();
    }

    bool read(const char* file)
    {
        this->ifs.open(file);
        if (this->ifs.good()) {
            this->content = string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

            return true;
        }
        _E(std::string("failed to open " + string(file)));
        return false;
    }

    void findline(const char* strstart)
    {
        string line;

        ifs.clear();
        ifs.seekg(0);

        while (getline(ifs, line))
        {
            if (line.find(strstart) == 0)
            {
                this->content = line;
                _D("read line");
                break;
            }
        }
        _E(string("could not find " + string(strstart) +" in file"));
    }

    void parsekeymap()
    {
        string str = this->content;

        map<string, vector<KeyObj>> keyMap;

        size_t pos = str.find("ActionKeyList");
        size_t absEndPos = str.find("AxisKeyList");

        size_t len = string("ActionName=\"").length();
        size_t lpos = 0;

        while (pos < absEndPos)
        {
            pos = str.find("ActionName=\"", pos + 1) + len;
            
            _D(lpos << " " << pos << " " << absEndPos);

            if (lpos > pos)
                break;

            size_t end = str.find("\"", pos );

            //_D("start: " << pos << "\nend: " << end);

            string action = str.substr(pos, end - pos);

            pos = str.find("Keys=(", pos) + string("Keys=").size();

            size_t depth = 0;
            size_t tpos = pos;

            string keystr = "";

            while(true)
            {
                char c = str.at(tpos);
                switch (c)
                {
                case '(':
                    depth += 1;
                    break;
                case ')':
                    depth -= 1;
                    break;
                default:
                    break;
                }
                //_D(c << " - " << depth);

                tpos += 1;

                if (depth <= 0) {
                    break;
                }
            }
            keystr = str.substr(pos, tpos - pos);

            vector<string> keyarr = splitArray(keystr);

            vector<KeyObj> ks;

            for (size_t i = 0; i < keyarr.size(); i++)
            {
                string obj = keyarr.at(i);
                if (obj.length() == 2)
                    continue;

                KeyObj ko;
                ko.key = getObjectValue(obj, "Key");

                if (getObjectValue(obj, "bCtrl") != "")
                    ko.bCtrl = true;

                if (getObjectValue(obj, "bShift") != "")
                    ko.bShift = true;

                ks.push_back(ko);
            }

            _D(action << " - " << ks.at(0).key);

            //keyMap.insert({ action,ks });

            lpos = pos;
            //_D(pos << " - " << action << " - " << keyarr);
            _D("EE");
        }
        _D("???");

    }

    string getObjectValue(string object, string specifier)
    {
        size_t pos = object.find(specifier) + specifier.length() + 1;

        if (pos > object.length())
            return "";

        size_t end = object.find_first_of("),\"", pos + 1);

        return object.substr(pos, end - pos);
    }

    vector<string> splitArray(string str)
    {
        size_t start = 0;
        size_t pos = 0;
        size_t depth = 0;

        vector<string> arr;

        while (true)
        {
            char c = str.at(pos);
            switch (c)
            {
            case '(': {
                depth++;
                if (depth == 2) {
                    start = pos;
                }
                break;
            }
            case ')': {
                depth--;
                
                if (depth == 1) {
                    string element;

                    element = str.substr(start,pos - start + 1);
                    arr.push_back(element);
                }
                break;
            }
            default:
                break;
            }
            if (depth <= 0)
                break;
            
            pos++;
        }

        //_DARR(arr);

        return arr;
    }
};

int main()
{
    Parser parse("GameUserSettings.ini");
    parse.findline("CustomInputSettings");
    parse.parsekeymap();
    system("pause");
}