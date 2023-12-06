#include <vector>
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
};

vector<int> parts;
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
int update_table(string data_file_path, int ***table)
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
                        int *p_num = table[i][j - 1];
                        *p_num = *p_num * 10 + digit;
                        table[i][j] = p_num;
                    }
                    else
                    {
                        // create number
                        parts.push_back(digit);
                        cout << "creat part at " << i << ", " << j << endl;
                        table[i][j] = &(parts.back());
                        reading_num = true;
                    }
                }
                else
                {
                    table[i][j] = nullptr;
                    reading_num = false;
                    if (c != '.')
                        symboles.push_back(point({i, j}));
                }
                j++;
            }
        }
        cout << "number of parts: " << parts.size() << endl;
    }
    else
    {
        cout << "file not open :/" << endl;
    }
    return 0;
}

bool in_bound(int i, int j, int ni, int nj)
{
    return (i) > 0 &&
           (j) > 0 &&
           (i) < ni &&
           (j) < nj;
}

int count_part_from_table(int ***table, int ni, int nj)
{
    int current_val = 0;
    int res = 0;
    for (point p : symboles)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i != 0 || j != 0)
                {
                    if (in_bound(p.i + i, p.j + j, ni, nj))
                    {
                        int *p_val = table[p.i + i][p.j + j];
                        if (p_val != nullptr && *p_val != current_val)
                        {
                            cout << "p_val:" << p_val << endl;
                            res += *p_val;
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    string data_file_path = "../data/input_day3_test.txt";

    int ni, nj;
    get_engine_size(data_file_path, ni, nj);
    cout << "ni: " << ni << "\tnj: " << nj << endl;

    // create a 2D array that contain pointer on part stored in vector 'parts'
    int ***table = (int ***)malloc(ni * sizeof(int **));
    for (int i = 0; i < ni; i++)
    {
        table[i] = (int **)malloc(nj * sizeof(int *));
    }

    // for (int i = 0; i < ni; ++i)
    // {
    //     for (int j = 0; j < nj; ++j)
    //     {
    //         table[i][j] = 0;
    //         cout << setw(2) << table[i][j] << "; ";
    //     }
    //     cout << endl;
    // }

    update_table(data_file_path, table);
    int res = count_part_from_table(table, ni, nj);
    cout << "res :" << res << endl;

    return 0;
}