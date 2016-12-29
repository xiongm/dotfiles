#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map> 
#include <unordered_set>
#include <queue>

using namespace std;
struct Relationship
{
  string item1;
  string item2;
  double prob;
};


struct Comparator
{

  bool operator() (const pair<string,int> & lhs, const pair<string,int> & rhs)
  {
    if (lhs.second == rhs.second)
    {
      return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second; 
  }
};

int main(int argc, char *argv[])
{

  double th;
  int n;
  cin >> th;
  cin >> n;
  cin.ignore();
  vector<Relationship> relationships;

  for (auto i = 0; i < n; i++)
  {
    string s;
    getline(cin,s);
    istringstream iss(s);
    Relationship relation;
    iss >> relation.item1;
    iss >> relation.item2;
    iss >> relation.prob;
    relationships.push_back(relation);
  }


  // what if duplicates
  unordered_map<string, pair<string, double>> relation_hash;
  for (auto &i : relationships)
  {
    relation_hash[i.item1] = make_pair(i.item2, i.prob);
  }



  priority_queue<pair<string,int>,vector<pair<string,int>>, Comparator> pqueue;


  for (auto &i : relationships)
  {
    {
      vector<string> cluster = {i.item1};
      string curr = cluster.back();
      while(relation_hash.count(curr) && relation_hash[curr].second > th)
      {
        cluster.push_back(relation_hash[curr].first);
        relation_hash.erase(curr);
        curr = cluster.back();
      }
      pqueue.push(make_pair(cluster.front(), cluster.size()));
    }
  }

  cout << pqueue.top().first << endl;
  
  return 0;
}
