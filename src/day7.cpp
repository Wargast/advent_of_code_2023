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

enum card
{
    J,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    T,
    Q,
    K,
    A,
};

enum hand_type
{
    HighCard,
    OnePair,
    twoPair,
    threeOf,
    FullHouse,
    fourOf,
    fiveOf,
};

class Hand
{
private:
    vector<card> cards;
    string str_cards;
    int bid;
    hand_type type;

public:
    Hand(string h, int bid) : bid(bid), str_cards(h)
    {
        for (auto c : h)
        {
            cards.push_back(get_type(c));
        }
        update_type();
    }
    int get_bid()
    {
        return bid;
    }
    vector<card> get_cards()
    {
        return cards;
    }

    card get_type(char c)
    {
        switch (c)
        {
        case 'A':
            return (card::A);
            break;
        case 'K':
            return (card::K);
            break;
        case 'Q':
            return (card::Q);
            break;
        case 'J':
            return (card::J);
            break;
        case 'T':
            return (card::T);
            break;
        case '9':
            return (card::nine);
            break;
        case '8':
            return (card::eight);
            break;
        case '7':
            return (card::seven);
            break;
        case '6':
            return (card::six);
            break;
        case '5':
            return (card::five);
            break;
        case '4':
            return (card::four);
            break;
        case '3':
            return (card::three);
            break;
        case '2':
            return (card::two);
            break;
        default:
            throw std::invalid_argument("unrecognized card: " + c);
        }
    }

    void update_type()
    {
        vector<int> card_count(card::A + 1, 0);
        int j_count = 0;
        for (auto c : cards)
        {
            if (c == card::J)
            {
                j_count++;
                // add 1 to all cards
                for (int i = 0; i < card_count.size(); i++)
                {
                    card_count[i]++;
                }
            }
            else
                card_count[c]++;
        }
        sort(card_count.rbegin(), card_count.rend());
        // cout << str_cards << endl
        //      << card_count[0] << ", " << card_count[1] << ", " << card_count[2] << endl;

        if (card_count[0] == 5)
        {
            type = hand_type::fiveOf;
        }
        else if (card_count[0] == 4)
        {
            type = hand_type::fourOf;
        }
        else if (card_count[0] == 3)
        {
            // on retir j count car pris en compte dans card_count[0]
            if ((card_count[1] - j_count) == 2)
                type = hand_type::FullHouse;
            else
                type = hand_type::threeOf;
        }
        else if (card_count[0] == 2)
        {
            // on retir j count car pris en compte dans card_count[0]
            if ((card_count[1] - j_count) == 2)
                type = hand_type::twoPair;
            else
                type = hand_type::OnePair;
        }
        else
            type = hand_type::HighCard;

        // cout << "type: " << type << endl
        //  << endl;
    }

    ~Hand()
    {
    }

    friend bool operator<(Hand &h1, Hand &h2)
    {
        if (h1.type == h2.type)
        {
            int i = 0;
            while (h1.cards[i] == h2.cards[i])
            {
                i++;
            }
            return (h1.cards[i] < h2.cards[i]);
        }
        else
        {
            return h1.type < h2.type;
        }
    }

    friend ostream &operator<<(ostream &os, const Hand &h)
    {
        os << h.str_cards;
        return os;
    }
};

long long str2int(string str)
{
    long long res = 0;
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

int main(int argc, char const *argv[])
{
    // string data_file_path = "../data/input_day7.txt";
    // string data_file_path = "../data/input_day7_test.txt";
    string data_file_path = argv[1];
    ifstream file;
    file.open(data_file_path);

    if (file.is_open())
    {
        string line;
        vector<Hand> hands;
        while (file.good())
        {
            getline(file, line);
            vector<string> words = split(line, " ");
            hands.push_back(Hand(words[0], str2int(words[1])));
        }
        sort(hands.begin(), hands.end());
        long long total_gain = 0;
        for (int i = 0; i < hands.size(); i++)
        {
            long long res = hands[i].get_bid() * (i + 1);
            cout << "hand " << hands[i] << " bid: " << hands[i].get_bid() << " * " << (i + 1) << " = " << res << endl;
            total_gain += res;
        }
        cout << "total gain: " << total_gain << endl;
    }
    return 0;
}
