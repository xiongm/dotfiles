#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;
void usage()
{
  cout << "word_searcher [file_name]" << endl;
}

void initialize_dict(const char * file, unordered_map<string, unordered_set<int>> & index_dict, vector<string> & dict)
{
  index_dict.reserve(10000);
  ifstream ifs(file);
  if (ifs.is_open())
  {
    while (ifs.good())
    {
      string line;
      getline(ifs, line);
      dict.push_back(line);
      istringstream iss(line);

      string word;
      int index = dict.size() - 1;
      for (auto i = istream_iterator<string>(iss); i != istream_iterator<string>(); i++)
      {
        index_dict[*i].insert(index);
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    usage();
    return -1;
  }


  string file_name (argv[1]);
  unordered_map<string, unordered_set<int>> index_dict;
  vector<string> dict;
  initialize_dict(file_name.c_str(), index_dict, dict);


  while(1)
  {
    cout << "Enter a word to search for:";
    string word;
    cin >> word;
    if (!index_dict.count(word))
      cout << word << " does not exist" << endl;
    else
    {
      for (auto i : index_dict[word])
      {
        cout << dict[i] << endl;
      }
    }
  }


  return 0;
}
