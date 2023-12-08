#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int string2int(string s);
void parse_card(string line, vector<int> &wining_nbs, vector<int> &my_nbs);

int string2int(string s)
{
    int res = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
            res += (int)(s[i] - '0') * (pow(10, s.size() - 1 - i));
    }
    return res;
}

void parse_card(string line, vector<int> &wining_nbs, vector<int> &my_nbs)
{
    /*
    Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    */
    line.erase(0, line.find(": ") + 2);
    int pos = 0;
    string wining_card = line.substr(0, line.find('|'));
    string my_card = line.erase(0, line.find("| ") + 2) + ' ';
    while ((pos = wining_card.find(' ')) != string::npos)
    {
        if (pos != 0)
        {
            wining_nbs.push_back(
                string2int(wining_card.substr(0, pos)));
        }

        wining_card.erase(0, pos + 1);
    }
    while ((pos = my_card.find(' ')) != string::npos)
    {
        if (pos != 0) // skip of doucle space
        {
            my_nbs.push_back(
                string2int(my_card.substr(0, pos)));
        }

        my_card.erase(0, pos + 1);
    }
}

int count_gain(vector<int> win_card, vector<int> mycard)
{
    int res = 1;
    for (auto nb : win_card)
    {
        if (find(mycard.begin(), mycard.end(), nb) != mycard.end())
        {
            res = res << 1;
        }
    }
    res = res >> 1;
    return res;
}

int count_matching(vector<int> win_card, vector<int> mycard)
{
    int res = 0;
    for (auto nb : win_card)
    {
        if (find(mycard.begin(), mycard.end(), nb) != mycard.end())
        {
            res++;
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day4.txt";
    ifstream myfile;
    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        string mystring;
        int tot_card_number = 0;
        int current_card_nb;
        vector<int> next_cards(1, 1);

        while (myfile.good())
        {
            getline(myfile, mystring);
            cout << "-> " << mystring << endl;
            vector<int> wining_nbs, my_nbs;

            if (next_cards.size())
            {
                current_card_nb = next_cards[0];
                next_cards.erase(next_cards.begin());
            }
            else
                current_card_nb = 1;

            tot_card_number += current_card_nb;
            parse_card(mystring, wining_nbs, my_nbs);

            // int gain = count_gain(wining_nbs, my_nbs);
            int matching_number = count_matching(wining_nbs, my_nbs);

            // update queue
            for (int i = 0; i < matching_number; i++)
            {
                if (i >= next_cards.size())
                {
                    next_cards.push_back(1 + current_card_nb);
                }
                else
                {
                    next_cards[i] += current_card_nb;
                }
            }
            cout << "tot card number: " << tot_card_number << endl;
        }
    }
    else
    {
        cout << "file not open :/" << endl;
    }

    return 0;
}
