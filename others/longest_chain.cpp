//#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int longest_chain_i(string word, unordered_map<string, int> & longest_dict) {
  int longest = 1; 
  for (size_t i = 0; i < word.size(); i++) {
    string next(word);
    next.erase(i, 1);
    if (longest_dict.count(next)) {
       longest = max(longest, longest_dict[next] + 1);
    }
  }
  return longest;
   
}

int longest_chain(vector<string> words) {
  sort(words.begin(), words.end(), [](const string & l, const string & r) {
    return l.size() < r.size(); 
  });
  unordered_map<string, int> longest_dict;
  for (auto word: words) {
    longest_dict[word] = 1;
  }
  
  for (auto word: words) {
    longest_dict[word] = longest_chain_i(word, longest_dict);
  }
  int longest = numeric_limits<int>::min();
  for (auto v : longest_dict) {
    longest = max(longest, v.second);
  }
  return longest;
}

int main(int argc, char *argv[])
{
  int length;
  cin >> length;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> words;
  for (int i = 0; i < length; i++) {
     std::string word;
     getline(cin, word);
     words.push_back(word);
  }
  int res = longest_chain(words);
  cout << res << endl;
  return 0;
}
