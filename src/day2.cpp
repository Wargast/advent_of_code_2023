#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct set
{
    int r, g, b;
};
ostream &operator<<(ostream &os, set const &s)
{
    return os << "{r:" << s.r << ", g:" << s.g << ", b:" << s.b << "}";
}
ostream &operator<<(ostream &os, vector<set> const &gs)
{
    // os << endl;
    for (auto s : gs)
    {
        os << s << endl;
    }
    return os;
}
const set bag = {12, 13, 14};

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

int update_set_from_str(string color, set &s)
{
    int color_pos = 0;
    if ((color_pos = color.find(" red")) != string::npos)
    {
        s.r = string2int(color.substr(0, color_pos));
        return 0;
    }
    else if ((color_pos = color.find(" green")) != string::npos)
    {
        s.g = string2int(color.substr(0, color_pos));
        return 1;
    }
    else if ((color_pos = color.find(" blue")) != string::npos)
    {
        s.b = string2int(color.substr(0, color_pos));
        return 2;
    }
    else
    {
        return -1;
    }
}

int parse_and_check_sets(string line)
{
    /* parse a line to get all the set
    example of game :
    Game 1: 7 green, 14 red, 5 blue; 8 red, 4 green; 6 green, 18 red, 9 blue
    */
    // parse game number
    string game_delimiter = ":";
    int id_pos = line.find(game_delimiter);
    int game_id = string2int(line.substr(5, id_pos - 5));
    cout << "Game " << game_id << " ";

    // parse sets
    int power = 0;
    set max_set = {0, 0, 0};
    bool is_valid = true;
    int set_pos = id_pos;
    string set_delim = ";";
    string cube_delim = ",";
    while (set_pos != string::npos && is_valid)
    {
        // cout << "pose:" << set_pos << " on " << line.size() << endl;
        int next_set_pos = line.find(set_delim, set_pos + 1);
        string set_string = line.substr(set_pos + 1, next_set_pos - set_pos);

        int first_cube = set_string.find(cube_delim);
        int second_cube = set_string.find(cube_delim, first_cube + 1);

        set current_set = {0, 0, 0};
        update_set_from_str(
            set_string.substr(0, first_cube),
            current_set);
        if (first_cube != string::npos)
        {
            // 3 cube colors
            update_set_from_str(
                set_string.substr(first_cube + 1, second_cube - first_cube - 1),
                current_set);
        }
        if (second_cube != string::npos)
        {
            // 3 cube colors
            update_set_from_str(
                set_string.substr(second_cube + 1),
                current_set);
        }
        set_pos = next_set_pos;

        // is_valid = current_set.r <= bag.r &&
        //            current_set.g <= bag.g &&
        //            current_set.b <= bag.b;

        if (current_set.r > max_set.r)
            max_set.r = current_set.r;
        if (current_set.g > max_set.g)
            max_set.g = current_set.g;
        if (current_set.b > max_set.b)
            max_set.b = current_set.b;
        if (!is_valid)
            cout << "KO because of " << current_set << endl;
    }
    power = max_set.r * max_set.g * max_set.b;
    // if (is_valid)
    // {
    //     cout << "OK  ! adding " << game_id << endl;
    //     return game_id;
    // }

    // return 0;
    cout << "power: " << power << endl;
    return power;
}

int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day2.txt";
    ifstream myfile;

    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        int total = 0;
        cout << "inital bag contain " << bag.r << " red ball, " << bag.g << " green balls, " << bag.b << " blue balls" << endl;
        string mystring;
        int ind_line = 1;
        while (myfile.good())
        {
            // mystring = "Game 13: 2 green; 8 green, 1 blue, 12 red; 1 blue, 14 green, 2 red; 1 blue, 6 red, 6 green; 7 green, 10 red";
            getline(myfile, mystring);
            // cout << "process string: " << mystring << endl;
            cout << ind_line << " - ";
            int game_set_sum = parse_and_check_sets(mystring);
            // cout << game_set << endl;
            total += game_set_sum;
            // break;
            ind_line++;
        }
        cout << "total: " << total << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }

    return 0;
}
