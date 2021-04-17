#include <iostream>
#include <vector>
#include <Windows.h>


#include <map>

using namespace std;


int main(int argc, char* argv[])
{
    vector<int>* vec = new vector<int>{ 1,2,3,4,5 };

    std::swap(vec->at(0), vec->at(2));

    cout << "VEC:{";

    for (size_t i = 0; i < vec->size(); i++)
    {
        cout << vec->at(i);
        if(i < vec->size())
            cout << ", ";
    }
    cout << "}" << endl;

    system("pause");
    return 0;
}