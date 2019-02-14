#include <bits/stdc++.h>

using namespace std;

int qfind(unordered_map<int, int> & parents, int i) {
  auto parent = i;
  while (parents.count(parent) && parents[parent] != parent) {
    parent = parents[parent];
  }
  return parent;
}

void qunion(unordered_map<int, int> & parents, int i, int j) {
  int pi = qfind(parents, i);
  int pj = qfind(parents, j);
  parents[max(pi, pj)] = min(pi, pj);

}

int findCircleNum(vector<vector<int>>& M) {
  unordered_map<int, int> parents;
  for (int i = 0; i < M.size(); i++)
  {
    for (int j = i; j < M.size(); j++)
    {
      if (M[i][j]) {
        qunion(parents, i, j);
      }
    }
  }

  unordered_set<int> counters;
  for (auto v : parents) {
    counters.insert(qfind(parents, v.first));
  }
  return counters.size();
}

int main(int argc, char *argv[])
{
  int length;
  cin >> length;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector< vector<int>> M(length, vector<int>(length, 0));
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      char r;
      cin >> r;
      M[i][j] = r - '0';
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  int res = findCircleNum(M);
  cout << res << endl;
  return 0;
}
