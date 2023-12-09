#include <vector>
#include <math.h>
#include <algorithm>
// #include <bits/stdc++.h>
#include <numeric>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

unsigned long long str2int(string str)
{
    unsigned long long res = 0;
    for (auto c : str)
    {
        if (isdigit(c))
            res = res * 10 + (c - '0');
        // cout << res << endl;
    }
    return res;
}

vector<string> split(string s, string delim)
{
    int pos = 0;
    vector<string> splitted;
    while ((pos = s.find(delim)) != string::npos)
    {
        if (pos != 0)
            splitted.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    splitted.push_back(s);
    return splitted;
}

int get_wins_nb(float tot_time, float record)
{
    int dist;
    float nb_wins = 0;
    long double borne1 = (-tot_time + sqrt(tot_time * tot_time - 4 * record)) / -2;
    long double borne2 = (-tot_time - sqrt(tot_time * tot_time - 4 * record)) / -2;

    nb_wins = floor(borne2) - floor(borne1) - (floor(borne1) == borne1);
    cout << "b1 " << borne1 << ", b2 " << borne2 << ", nbw " << nb_wins << endl;
    return nb_wins;
}

int main(int argc, char const *argv[])
{

    string data_file_path = "../data/input_day6.txt";
    ifstream file;
    file.open(data_file_path);

    if (file.is_open())
    {
        string line, accumulated_line;
        vector<string> splitted;
        vector<unsigned long long> times, records;
        unsigned long long times_sum, records_sum;

        cout << "get times ..." << endl;
        getline(file, line);
        // cout << line << endl;
        splitted = split(line, " ");
        accumulated_line = accumulate(splitted.begin() + 1, splitted.end(), string(""));
        times_sum = str2int(accumulated_line);
        cout << line << "  --> tot: " << accumulated_line << " --> " << times_sum << endl;
        for (int i = 1; i < splitted.size(); i++)
        {
            times.push_back(str2int(splitted[i]));
        }

        cout << "get records ..." << endl;
        getline(file, line);
        splitted = split(line, " ");
        accumulated_line = accumulate(splitted.begin() + 1, splitted.end(), string(""));
        records_sum = str2int(accumulated_line);
        cout << line << "  --> tot: " << accumulated_line << " --> " << records_sum << endl;
        for (int i = 1; i < splitted.size(); i++)
        {
            records.push_back(str2int(splitted[i]));
        }

        int res = 1;
        int wins;
        for (int i = 0; i < times.size(); i++)
        {
            wins = get_wins_nb(times[i], records[i]);
            res *= wins;
            cout << "wins nb: " << wins << endl;
        }
        cout << "res1: " << res << endl
             << endl;

        wins = get_wins_nb(times_sum, records_sum);
        cout << "res2: " << wins << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }
    return 0;
}
