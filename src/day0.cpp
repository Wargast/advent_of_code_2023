
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day1.txt";
    ifstream myfile;

    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        string mystring;
        while (myfile.good())
        {
            getline(myfile, mystring);
            cout << "process string: " << mystring << endl;
        }
    }
    else
    {
        cout << "file not open :/" << endl;
    }

    return 0;
}
