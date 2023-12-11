#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

int string2int(string s);

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

class Map
{
private:
    vector<int> map;
    int max_value = 0;

public:
    Map()
    {
    }
    Map(int size) : map(size, -1)
    {
        cout << " create map of size " << size << endl;
        for (int i = 0; i < size; i++)
        {
            map[i] = i;
        }
        max_value = size;
    }

    ~Map()
    {
    }

    void resize(int size)
    {
        map.resize(size);
    }

    int max()
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
            cout << "-> " << line << "------" << line.size() << endl;
            vector<string> line_values = split(line, " ");
            update(
                string2int(line_values[0]),
                string2int(line_values[1]),
                string2int(line_values[2]));
            getline(file, line);
        }
        return 0;
    }

    int update(
        int des_range_start,
        int source_range_start,
        int range_length)
    {
        int i = 0;
        while (i < range_length && i < (map.size() - source_range_start))
        {
            map[source_range_start + i] = des_range_start + i;
            i++;
        }
        max_value = std::max(max_value, des_range_start + i);
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

    int &operator[](int index)
    {
        return map[index];
    }
};

int get_loc(
    Map seed2soil,
    Map soil2fert,
    Map fert2water,
    Map water2light,
    Map light2temp,
    Map temp2hum,
    Map hum2loc,
    int seed)
{
    int soil = seed2soil[seed];
    int fert = soil2fert[soil];
    int water = fert2water[fert];
    int light = water2light[water];
    int temp = light2temp[light];
    int hum = temp2hum[temp];
    int loc = hum2loc[hum];

    std::cout << "seed " << seed << " -> ";
    std::cout << "soil " << soil << " -> ";
    std::cout << "fert " << fert << " -> ";
    std::cout << "water " << water << " -> ";
    std::cout << "light " << light << " -> ";
    std::cout << "temp " << temp << " -> ";
    std::cout << "hum " << hum << " -> ";
    std::cout << "loc " << loc << std::endl;
    return loc;
}

int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day5.txt";
    ifstream myfile;
    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        string mystring;

        vector<int> seeds;
        getline(myfile, mystring);
        vector<string> splitted = split(mystring, " ");
        cout << "seeds: ";
        for (int i = 1; i < splitted.size(); i++)
        {
            seeds.push_back(string2int(splitted[i]));
            cout << splitted[i];
        }
        cout << endl;

        // Map seed2soil, soil2fert, fert2water, water2light, light2temp, temp2hum, hum2loc;

        getline(myfile, mystring); // get first emptyline
        // create seed2soil
        int max_seed = *max_element(seeds.begin(), seeds.end());
        Map seed2soil(max_seed + 1);
        seed2soil.create_from_file(myfile);
        // cout << seed2soil << endl;

        // cout << "next map" << endl;
        Map soil2fert(seed2soil.max());
        soil2fert.create_from_file(myfile);
        // cout << soil2fert << endl;

        // cout << "map  fert2wat" << endl;
        Map fert2water(soil2fert.max());
        fert2water.create_from_file(myfile);
        // cout << fert2water << endl;

        // cout << "map  water2light" << endl;
        Map water2light(fert2water.max());
        water2light.create_from_file(myfile);
        // cout << water2light << endl;

        // cout << "map  light2te" << endl;
        Map light2temp(water2light.max());
        light2temp.create_from_file(myfile);
        // cout << light2temp << endl;

        // cout << "map  temp2h" << endl;
        Map temp2hum(light2temp.max());
        temp2hum.create_from_file(myfile);
        // cout << temp2hum << endl;

        // cout << "map  hum2l" << endl;
        Map hum2loc(temp2hum.max());
        hum2loc.create_from_file(myfile);
        // cout << hum2loc << endl;

        int min_location = hum2loc.max();
        for (auto seed : seeds)
        {
            int loc = get_loc(seed2soil, soil2fert, fert2water, water2light, light2temp, temp2hum, hum2loc, seed);
            min_location = std::min(min_location, loc);
        }
        cout << "min loc number: " << min_location << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }

    return 0;
}
