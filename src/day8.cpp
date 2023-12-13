#include <algorithm>
/* #include <exception> */
#include <fstream>
/* #include <iomanip> */
#include <iostream>
#include <map>
/* #include <math.h> */
#include <numeric>
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

struct vertex {
  typedef vertex *ve;
  ve right, left;
  string name;
  vertex(string s) : name(s) {}
};

class graph {
public:
  typedef map<string, vertex *> vmap;
  vmap work;
  string instructions;
  vertex *start;
  void addvertex(const string &);
  void addedge(const string &from, const string &to, char pos);
  vertex *apply_intructions(vertex *start);
  vector<vertex *> get_path_to_end(vertex *start);
};

vertex *graph::apply_intructions(vertex *start) {
  vertex *pos = start;
  for (int i = 0; i < instructions.size(); i++) {
    char dir = instructions[i];
    if (dir == 'R') {
      pos = pos->right;

    } else {
      pos = pos->left;
    }
  }
  return pos;
}
void graph::addvertex(const string &name) {
  vmap::iterator itr = work.find(name);
  if (itr == work.end()) {
    vertex *v;
    v = new vertex(name);
    work[name] = v;
    return;
  }
  /* cout << "\nVertex already exists!" << endl; */
}

void graph::addedge(const string &from, const string &to, char pos) {
  vertex *f = (work.find(from)->second);
  vertex *t = (work.find(to)->second);
  vertex *edge = t;
  if (pos == 'L') {
    f->left = edge;
  } else {
    f->right = edge;
  }
}

vector<vertex *> graph::get_path_to_end(vertex *start) {
  vector<vertex *> path;
  path.push_back(start);
  vertex *current_v = start;

  current_v = apply_intructions(current_v);
  while (current_v->name[2] != 'Z') {
    path.push_back(current_v);
    current_v = apply_intructions(current_v);
  }
  path.push_back(current_v);
  return path;
}

void push_line_to_graph(graph &g, string line) {
  vector<string> v_name_edges = split(line, " = ");
  string current_vert = v_name_edges[0];
  g.addvertex(current_vert);
  string v_left = v_name_edges[1].substr(2 + 1, 3);
  string v_right = v_name_edges[1].substr(2 + 6, 3);
  g.addvertex(v_left);
  g.addvertex(v_right);
  g.addedge(current_vert, v_left, 'L');
  g.addedge(current_vert, v_right, 'R');
}

long long brute_force_solution(vector<vertex *> current_verts, graph g) {
  // start walksng
  long long i = 0;
  bool end = false;
  while (!end) {
    int end_counter = 0;
    for (int i = 0; i < current_verts.size(); i++) {
      current_verts[i] = g.apply_intructions(current_verts[i]);
      if (find(current_verts.begin(), current_verts.end(), current_verts[i]) !=
          current_verts.begin() + i) {
        current_verts.erase(current_verts.begin() + i);
      }
      if (current_verts[i]->name[2] == 'Z') {
        end_counter++;
      }
    }
    end = end_counter == current_verts.size();
    i++;
    cout << "\rnbr of current_verts: " << current_verts.size()
         << "  counter: " << i * g.instructions.size();
  }
  cout << endl;
  return i;
}

long long smart_solve_multiple_start(vector<vertex *> current_verts, graph g) {
  vector<long long> cycle_length(current_verts.size(), 0);
  for (int i = 0; i < current_verts.size(); i++) {
    vector<vertex *> path = g.get_path_to_end(current_verts[i]);
    cycle_length[i] = path.size() - 1;
    cout << "cycle length: " << cycle_length[i] << endl;
    cout << path[0]->name << " -> " << path[1]->name << " -> " << path[2]->name
         << " ... " << path[path.size() - 1]->name << " -> "
         << g.apply_intructions(path[path.size() - 1])->name << " ... " << endl;
  }
  long long g_lcm = 1;
  for (auto l : cycle_length) {
    g_lcm = std::lcm(g_lcm, l);
  }

  return g_lcm;
}

int main(int argc, char const *argv[]) {
  // string data_file_path = "../data/input_day7.txt
  /* string data_file_path = "../data/input_day8.txt"; */
  string data_file_path = argv[1];
  ifstream file;
  file.open(data_file_path);

  string line;
  graph g;

  if (file.is_open()) {
    getline(file, g.instructions);
    /* getline(file, line); */

    getline(file, line); // catch empty line

    // fullfill graph
    while (file.good()) {
      getline(file, line);
      push_line_to_graph(g, line);
    }
    std::cout << "instructions: " << g.instructions << std::endl;

    vector<vertex *> current_verts;
    for (auto const &x : g.work) {
      std::cout << x.first << " : " << x.second->left->name << " | "
                << x.second->right->name << std::endl;
      if (x.first[2] == 'A') {
        current_verts.push_back(x.second);
      }
    }

    /* current_vrts.clear(); */
    /* current_verts.push_back(g.work.find("AAA")->second); */
    cout << "starting vert: ";
    for (auto v : current_verts) {
      cout << v->name << ", ";
    }
    cout << endl;

    /* long long i = brute_force_solution(current_verts, g); */
    long long i = smart_solve_multiple_start(current_verts, g);

    std::cout << "intruction counter: " << i * g.instructions.size()
              << std::endl;
  }
}
