#include <vector>
// #include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
/* test res = 4361
467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
*/

struct point
{
    int i, j;
    int val = 0;
};

vector<int> parts;
vector<point> gears;
vector<point> symboles;

int get_engine_size(string file, int &ni, int &nj)
{
    ni = 0;
    nj = 0;
    ifstream myfile;
    myfile.open(file);

    if (myfile.is_open())
    {
        string line;
        getline(myfile, line);
        ni++;
        nj = line.size();
        while (myfile.good())
        {
            getline(myfile, line);
            ni++;
        }
    }
    else
    {
        cout << "file not open :/" << endl;
    }
    return 0;
}
void update_table(string data_file_path, int **table)
{
    ifstream myfile;
    myfile.open(data_file_path);
    if (myfile.is_open())
    {
        char c;
        int i = 0;
        int j = 0;
        bool reading_num = false;
        int num = 0;
        while (myfile.get(c))
        {
            if (c == '\n')
            {
                i++;
                j = 0;
                reading_num = false;
            }
            else
            {
                if (isdigit(c))
                {
                    int digit = c - '0';
                    if (reading_num)
                    {
                        int part_ind = table[i][j - 1];
                        parts[part_ind] = parts[part_ind] * 10 + digit;
                        table[i][j] = part_ind;
                    }
                    else
                    {
                        // create number
                        parts.push_back(digit);
                        // cout << "creat part at (" << i << ", " << j << ")" << endl;
                        table[i][j] = parts.size() - 1; // Store ind of part
                        reading_num = true;
                    }
                }
                else
                {
                    table[i][j] = -1;
                    reading_num = false;
                    if (c != '.')
                    {
                        point p = {i, j};
                        symboles.push_back(p);
                        if (c == '*')
                        {
                            gears.push_back(p);
                        }
                    }
                }
                j++;
            }
        }
        cout << "number of parts: " << parts.size() << endl;
        cout << "number of symboles: " << symboles.size() << endl;
        cout << "number of gears: " << gears.size() << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }
}

bool in_bound(int i, int j, int ni, int nj)
{
    return (i) >= 0 &&
           (j) >= 0 &&
           (i) < ni &&
           (j) < nj;
}

void filter_parts(int **table, int ni, int nj)
{
    vector<int> temp(parts.size(), 0);
    for (point p : symboles)
    {
        for (int i = -1; i < 2; i++)
        {
            int current_val_ind = -1;
            for (int j = -1; j < 2; j++)
            {
                if (i != 0 || j != 0)
                {
                    if (in_bound(p.i + i, p.j + j, ni, nj))
                    {
                        int I = p.i + i;
                        int J = p.j + j;
                        int part_ind = table[I][J];
                        if (part_ind != -1 && part_ind != current_val_ind)
                        {
                            // cout << "p_val:" << parts[part_ind] << " at (" << I << ", " << J << ")" << endl;
                            temp[part_ind] = parts[part_ind];
                            current_val_ind = part_ind;
                        }
                    }
                }
            }
        }
    }
    parts = temp;
}

void filter_gears(int **table, int ni, int nj)
{
    for (point &g : gears)
    {
        int count = 0;
        int temp = 1;
        for (int i = -1; i < 2; i++)
        {
            int current_val_ind = -1;
            for (int j = -1; j < 2; j++)
            {
                if (i != 0 || j != 0)
                {
                    int I = g.i + i;
                    int J = g.j + j;
                    if (in_bound(I, J, ni, nj))
                    {
                        int part_ind = table[I][J];
                        if (part_ind != -1 && part_ind != current_val_ind)
                        {
                            current_val_ind = part_ind;
                            count++;
                            temp *= parts[part_ind];
                        }
                    }
                }
            }
        }
        if (count == 2)
        {
            g.val = temp;
            // cout << "add gear g: (" << g.i << ", " << g.j << ") value " << g.val << endl;
        }
    }
}
int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day3.txt";
    string output_file_path = "output.txt";

    int ni, nj;
    get_engine_size(data_file_path, ni, nj);
    cout << "ni: " << ni << "\tnj: " << nj << endl;

    // create a 2D array that contain pointer on part stored in vector 'parts'
    int **table = (int **)malloc(ni * sizeof(int **));
    for (int i = 0; i < ni; i++)
    {
        table[i] = (int *)malloc(nj * sizeof(int *));
    }

    update_table(data_file_path, table);
    filter_parts(table, ni, nj);
    int res_parts = reduce(parts.begin(), parts.end());
    cout << "res_parts:" << res_parts << endl;

    int res_gear = 0;
    filter_gears(table, ni, nj);
    for (auto &g : gears)
    {
        res_gear += g.val;
    }
    cout << "res gears " << res_gear << endl;

    if (res_parts == 4361 && res_gear == 467835)
    {
        cout << "OK !" << endl;
    }
    else
    {
        cout << "KO expected 4361" << endl;
    }

    return 0;
}