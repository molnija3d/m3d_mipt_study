#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"\r\n\r\n","Hello world","Molnija3D"};

    for (const string& word : msg)
    {
        cout << word << " *** ";
    }
    cout << endl;
}