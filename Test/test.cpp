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
                _S("read line");
                return;
            }
        }
        _E(string("could not find " + string(strstart) +" in file"));
    }

    map<string, vector<KeyObj>> parsekeymap()
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
            
            //_D(lpos << " " << pos << " " << absEndPos);

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

                KeyObj ko = parseKeyObj(obj);
                ks.push_back(ko);
            }

            if(ks.size() != 0)
                keyMap.insert({ action,ks });

            //_D(action << " - ")// << ks.at(0).key);

            //keyMap.insert({ action,ks });

            lpos = pos;
            //_D(pos << " - " << action << " - " << keyarr);
        }

        return keyMap;
    }

    KeyObj parseKeyObj(string object)
    {
        KeyObj ko;

        size_t pos = object.find("Key=") + 4;

        ko.key = object.substr( pos,object.find(')') - pos);


        if (object.find("bShift=") != string::npos)
            ko.bShift = true;

        if (object.find("bCtrl=") != string::npos)
            ko.bCtrl = true;

        return ko;
    }

    string getObjectValue(string object, string specifier)
    {
        //object = "(Keys=LeftShift,bShift=False,foo=(())";

        size_t pos = object.find(specifier) + specifier.length() + 1;

        if (pos > object.length())
            return "";

        size_t end = object.find_first_of("),\"", pos + 1);

        string ret = object.substr(pos, end - pos);
        //_D(ret << " " << pos << " " << end-pos);


        return ret;
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
                    
                    if (element.compare("()") != 0) {

                        //_D(element);
                        arr.push_back(element);
                    }
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

//int main()
//{
//    map<string, vector<KeyObj>> actionkeylist;
//
//    Parser parse("GameUserSettings.ini");
//    parse.findline("CustomInputSettings");
//    actionkeylist = parse.parsekeymap();
//
//    system("pause");
//}

int main()
{
    string  path;
    ofstream file;

    char* libvar;
    size_t rSize;
    getenv_s(&rSize, NULL, 0, "appdata");
    if (rSize != 0)
    {
        libvar = (char*)malloc(rSize * sizeof(char));
        
        getenv_s(&rSize, libvar, rSize, "appdata");

        path = libvar;
        cout << "appdata=" << path << endl;
        path += "\\DoDLog.log";
        cout << "path=" << path << endl;
        file.open(path.c_str(), ios::out | ios::app);
    }
    system("pause");
    return 0;
}