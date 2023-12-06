
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
vector<string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int check_spelled(string s, int offset, int incr)
{
    for (int n = 0; n < numbers.size(); n++)
    {
        string num = numbers[n];
        int i_num = incr > 0 ? 0 : (num.size() - 1);
        int i_s = offset;
        bool pass_num = false;
        while ((0 <= i_num && i_num < num.size()) &&
               (0 <= i_s && i_s < s.size()) &&
               !pass_num)
        {
            // cout << "num letter " << num[i_num] << endl;
            if (num[i_num] != s[i_s])
            {
                // cout << "break" << endl;
                pass_num = true;
            }
            else
            {
                i_num += incr;
                i_s += incr;
            }
        }
        if (!pass_num)
        {
            // cout << "return " << n + 1 << endl;
            return n + 1;
        }
        else
        {
            // cout << "pass" << endl;
        }
    }
    return 0;
}

int getNumbers(string s)
{
    int condition = 2;
    int i_incr = 0;
    int i_decr = s.size() - 1;
    int res[2] = {0, 0};

    while (condition != 0 &&
           i_incr < s.size() &&
           i_decr >= 0)
    {
        if (res[0] == 0)
        {
            if (isdigit(s[i_incr]))
            {
                res[0] = s[i_incr] - '0';
                condition--;
            }
            else
            {
                int res_spell = check_spelled(s, i_incr, 1);
                if (res_spell)
                {
                    condition--;
                    res[0] = res_spell;
                }
            }
        }

        if (res[1] == 0)
        {
            if (isdigit(s[i_decr]))
            {
                res[1] = s[i_decr] - '0';
                condition--;
            }
            else
            {
                int res_spell = check_spelled(s, i_decr, -1);
                if (res_spell)
                {
                    condition--;
                    res[1] = res_spell;
                }
            }
        }
        i_incr++;
        i_decr--;
    }

    return res[0] * 10 + res[1];
}

int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day1.txt";
    ifstream myfile;
    int final_res = 0;

    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        string mystring;
        while (myfile.good())
        {
            getline(myfile, mystring);
            // Some process here under

            cout << "process string: " << mystring << endl;
            int res = getNumbers(mystring);
            // int res = check_spelled(mystring, mystring.size() - 1, -1);
            cout << "\tres: " << res << endl;
            final_res += res;
        }
        cout << "finale res: " << final_res << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }

    return 0;
}
