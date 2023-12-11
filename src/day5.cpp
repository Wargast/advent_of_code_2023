#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

long long string2longlong(string s);

vector<string> split(string s, string delim)
{
    vector<string> splitted;
    int pos = 0;
    while ((pos = s.find(delim)) != string::npos)
    {
        if (pos != 0) // skip of double delim
            splitted.push_back(
                s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    if (s.size())
        splitted.push_back(s);

    return splitted;
}

long long string2longlong(string s)
{
    long long res = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
            res += (long long)(s[i] - '0') * (pow(10, s.size() - 1 - i));
    }
    return res;
}

struct range
{
    long long start, end;
    long long offset;

    friend bool operator<(const range &r1, const range &r2)
    {
        return r1.start < r2.start;
    }

    friend ostream &operator<<(ostream &os, const range &r)
    {
        os << r.start << " -> " << r.end << " : " << r.offset;

        return os;
    }
};

class Map
{
private:
    vector<range> map;
    long long max_value = 0;

public:
    Map()
    {
    }

    ~Map()
    {
    }

    // // void resize(int size)
    // // {
    // //     map.resize(size);
    // // }

    long long max()
    {
        return max_value;
    }

    int create_from_file(ifstream &file)
    {
        string line;
        getline(file, line); // get map name
        getline(file, line); // get first line
        while (file.good() && line.size())
        {
            // cout << "-> " << line << "------" << line.size() << endl;
            vector<string> line_values = split(line, " ");
            update(
                string2longlong(line_values[0]),
                string2longlong(line_values[1]),
                string2longlong(line_values[2]));
            getline(file, line);
        }
        // sort map ranges
        sort(map.begin(), map.end());
        cout << "nb of ranges: " << map.size() << endl;
        return 0;
    }

    int update(
        long long des_range_start,
        long long source_range_start,
        long long range_length)
    {
        range r;
        r.start = source_range_start;
        r.end = source_range_start + range_length;
        r.offset = des_range_start - source_range_start;
        map.push_back(r);
        max_value = std::max(max_value, des_range_start + range_length);
        return 0;
    }

    friend ostream &operator<<(ostream &os, const Map &m)
    {
        os << endl;
        for (int i = 0; i < m.map.size(); i++)
        {
            os << setw(3) << i << " | " << setw(5) << m.map[i] << endl;
        }

        return os;
    }

    long long operator[](long long index)
    {
        long long value = -1;
        // search value in ranges
        for (int i = 0; i < map.size(); i++)
        {
            if (index >= map[i].start && index <= map[i].end)
            {
                value = map[i].offset + index;
            }
        }
        if (value == -1)
        {
            value = index;
        }
        // cout << index << " -> " << value << " | ";

        return value;
    }
};

long long get_loc(
    vector<Map> maps,
    long long seed)
{
    // cout << endl;

    long long soil = maps[0][seed];
    long long fert = maps[1][soil];
    long long water = maps[2][fert];
    long long light = maps[3][water];
    long long temp = maps[4][light];
    long long hum = maps[5][temp];
    long long loc = maps[6][hum];

    // cout << endl;
    // std::cout << "seed " << seed << " -> ";
    // std::cout << "soil " << soil << " -> ";
    // std::cout << "fert " << fert << " -> ";
    // std::cout << "water " << water << " -> ";
    // std::cout << "light " << light << " -> ";
    // std::cout << "temp " << temp << " -> ";
    // std::cout << "hum " << hum << " -> ";
    // std::cout << "loc " << loc << std::endl;
    return loc;
}

long long get_minimum_loc_from_range(vector<Map> maps_list, range r)
{
    long long min_loc = -1;
    long long step = 100000;

    // long long start_loc = get_loc(maps_list, r.start);
    // long long end_loc = get_loc(maps_list, r.end);
    for (long long i = r.start; i < r.end; i += min(step, r.end - i))
    {
        long long i_loc = get_loc(maps_list, i);
        long long i_loc_step = get_loc(maps_list, i + min(step, r.end - i));
        if (i_loc != i_loc_step - min(step, r.end - i))
        {
            for (long long j = 0; j < min(step, r.end - i); j++)
            {
                long long loc = get_loc(maps_list, j + i);
                if (min_loc == -1)
                    min_loc = loc;
                else
                    min_loc = std::min(loc, min_loc);
            }
        }
        else
        {
            // cout << "skip " << step << endl;
            if (min_loc == -1)
                min_loc = i_loc;
            else
                min_loc = std::min(i_loc, min_loc);
        }
    }
    return min_loc;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cerr << "No program parameters provided !" << endl;
        exit(EXIT_FAILURE);
    }
    string data_file_path = argv[1];
    // string data_file_path = "../data/input_day5_test.txt";
    ifstream myfile;
    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        string mystring;

        vector<long long> seeds;
        getline(myfile, mystring);

        vector<string> splitted = split(mystring, " ");
        cout << "seeds: ";
        for (int i = 1; i < splitted.size(); i++)
        {
            seeds.push_back(string2longlong(splitted[i]));
            cout << splitted[i] << ", ";
        }
        cout << endl;

        // Map seed2soil, soil2fert, fert2water, water2light, light2temp, temp2hum, hum2loc;

        getline(myfile, mystring); // get first emptyline
        // create seed2soil
        cout << "map seed2soil" << endl;
        Map seed2soil = Map();
        seed2soil.create_from_file(myfile);
        // cout << seed2soil << endl;
        // return 0;

        cout << "map soil2fert" << endl;
        Map soil2fert = Map();
        soil2fert.create_from_file(myfile);
        // cout << soil2fert << endl;

        cout << "map  fert2wat" << endl;
        Map fert2water = Map();
        fert2water.create_from_file(myfile);
        // cout << fert2water << endl;

        cout << "map  water2light" << endl;
        Map water2light = Map();
        water2light.create_from_file(myfile);
        // cout << water2light << endl;

        cout << "map  light2te" << endl;
        Map light2temp = Map();
        light2temp.create_from_file(myfile);
        // cout << light2temp << endl;

        cout << "map  temp2h" << endl;
        Map temp2hum = Map();
        temp2hum.create_from_file(myfile);
        // cout << temp2hum << endl;

        cout << "map  hum2l" << endl;
        Map hum2loc = Map();
        hum2loc.create_from_file(myfile);
        // cout << hum2loc << endl;

        vector<Map> maps_list = {
            seed2soil,
            soil2fert,
            fert2water,
            water2light,
            light2temp,
            temp2hum,
            hum2loc,
        };

        long long min_location = -1;
        for (int i = 0; i < seeds.size() - 1; i += 2)
        {
            range r;
            r.start = seeds[i];
            r.end = r.start + seeds[i + 1];
            cout << "process seeds " << r.start << " -> " << r.end << " (" << r.end - r.start << ")" << endl;
            long long range_min = get_minimum_loc_from_range(maps_list, r);
            cout << "\tmin: " << range_min << endl;
            if (min_location == -1)
                min_location = range_min;
            else
                min_location = std::min(min_location, range_min);
        }
        cout << "min loc number: " << min_location << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }

    return 0;
}