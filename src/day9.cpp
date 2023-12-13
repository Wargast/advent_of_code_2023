#include <algorithm>
/* #include <exception> */
#include <fstream>
/* #include <iomanip> */
#include <iostream>
#include <map>
/* #include <math.h> */
#include <numeric>
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

long long predict(vector<int> hist) {
  int n = hist.size();
  cout << "\t" << hist << endl;
  if (all_of(hist.begin(), hist.end(), [&](int i) { return i == 0; })) {
    return 0;
  } else {
    vector<int> diff(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
      diff[i] = (hist[i + 1] - hist[i]);
    }
    return hist[n - 1] + predict(diff);
  }
}
long long predict2(vector<int> hist) {
  int n = hist.size();
  cout << "\t" << hist << endl;
  if (all_of(hist.begin(), hist.end(), [&](int i) { return i == 0; })) {
    return 0;
  } else {
    vector<int> diff(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
      diff[i] = (hist[i + 1] - hist[i]);
    }
    return hist[0] - predict2(diff);
  }
}

int main(int argc, char const *argv[]) {
  string data_file_path = argv[1];
  ifstream file;
  file.open(data_file_path);

  string line;
  if (file.is_open()) {

    vector<vector<int>> oasis;

    while (file.good()) {
      getline(file, line);
      /* cout << line << endl; */
      if (line != "") {
        vector<string> splitted_data = split(line, " ");
        vector<int> data_hist(splitted_data.size(), 0);

        for (int i = 0; i < splitted_data.size(); i++) {
          data_hist[i] = str2int(splitted_data[i]);
        }
        oasis.push_back(data_hist);
      }
    }
    long long res = 0;
    long long res2 = 0;

    for (auto hist : oasis) {
      /* cout << "start prediction..." << endl; */
      int pred = predict(hist);
      res += pred;
      res2 += predict2(hist);
      cout << "pred: " << pred << endl;
    }
    cout << "res: " << res << endl;
    cout << "pred2: " << res2 << endl;
  }
}
