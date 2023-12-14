#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

long long str2int(string str) {
  long long res = 0;
  for (auto c : str) {
    if (isdigit(c))
      res = res * 10 + (c - '0');
    // cout << res << endl;
  }
  if (str[0] == '-') {
    res *= -1;
  }
  return res;
}

vector<string> split(string s, string delim) {
  int pos = 0;
  vector<string> splitted;
  while ((pos = s.find(delim)) != string::npos) {
    if (pos != 0)
      splitted.push_back(s.substr(0, pos));
    s.erase(0, pos + 1);
  }
  splitted.push_back(s);
  return splitted;
}

ostream &operator<<(ostream &os, vector<int> vect) {
  for (auto d : vect) {
    os << d << ", ";
  }
  return os;
}

struct point {
  char value;
  size_t x, y;
  int dist;
};

class Matrix {
  std::vector<point> m_Data;
  size_t rows, cols;
  point start_point;

public:
  Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    m_Data.resize(rows * cols);
  }

  char &operator()(size_t y, size_t x) { return m_Data[y * cols + x].value; }

  friend ostream &operator<<(ostream &os, Matrix &mat) {
    for (size_t i = 0; i < (mat.cols * mat.rows); i++) {
      if (i % mat.cols == 0) {
        os << endl;
      }
      os << mat.m_Data[i].value << " ";
    }
    return os;
  }

  // more methods go here
  void set_row(size_t y, string line) {
    for (size_t x = 0; x < cols; x++) {
      point p = {line[x], x, y, 0};
      m_Data[y * cols + x] = p;
    }
  }

  void set_start_point(size_t y, size_t x) {
    start_point = m_Data[y * cols + x];
  }

  point get_start_point() { return start_point; }
};

vector<point> get_max_loop(const Matrix f, point start_point) {
  vector<point> path;

  return path;
}

int main(int argc, char const *argv[]) {
  string data_file_path = argv[1];
  ifstream file;
  file.open(data_file_path);

  string line;
  if (file.is_open()) {

    getline(file, line);
    Matrix field(line.size(), line.size());

    field.set_row(0, line);
    size_t row = 0;

    while (file.good()) {
      getline(file, line);
      /* cout << line << endl; */
      if (line != "") {
        row++;
        field.set_row(row, line);
        size_t col = line.find('S');
        if (col != string::npos) {
          field.set_start_point(row, col);
        }
      }
    }

    cout << "field: " << field << endl;
    cout << field.get_start_point().x << " " << field.get_start_point().y
         << endl;

    vector<point> loop = get_max_loop(field, field.get_start_point());

    long long res = 0;
    long long res2 = 0;

    cout << "res: " << res << endl;
    cout << "pred2: " << res2 << endl;
  }
}
