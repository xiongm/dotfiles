#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;
string getNextPNumber(const string & curr)
{
  unordered_map<char, char> tb       {{'0', '1'}, 
                               {'1', '2'}, 
                               {'2', '3'},
                               {'3', '4'},
                               {'4', '5'},
                               {'5', '6'},
                               {'6', '7'},
                               {'7', '8'},
                               {'8', '9'},
                               {'9', 'a'},
                               {'a', 'b'},
                               {'b', 'c'},
                               {'c', 'd'},
                               {'d', 'e'},
                               {'e', 'f'},
                               {'f', 'g'},
                               {'g', '0'}};

  string res(curr);
  int const n = curr.size();

  int start = n / 2;
  if (n & 1) {
    for(int i = start, j = start; i >= 0 && j < n; i--, j++ )
    {
      res[i] = tb[res[i]];
      res[j] = res[i];
      if (res[i] == '0') continue;
      else return res;
    }
  }
  else
  {
    for(int i = start - 1, j = start; i >= 0 && j < n; i--, j++ )
    {
      res[i] = tb[res[i]];
      res[j] = tb[res[j]];
      if (res[i] == '0') continue;
      else return res;
    }

  }

  res.append(1,'0');
  res[0] = res[n] = '1';
  return res;
}

bool has17Consecutive1Bits(unsigned long long number)
{
  int count = 0;
  int i = 64;

  while(i-->0)
  {
    if (number & 1) {
      count++;
      if (17 == count) return true;
    } else
    {
      count = 0;
      if (i < 17) return false;
    }
    number >>= 1;
  }
  return false;
}

template <class T, int BASE>
T to_base10(const string & s)
{
  T res = 0;
  T base = 1;
  for (auto iter = s.rbegin(); iter < s.rend(); iter++)
  {
     int base10 = 0;
     if (*iter >= '0' && *iter <= '9')
     {
       base10 = *iter - '0';
     } else {
       base10 = *iter - 'a' + 10;
     }
     res += base * base10;
     base *= BASE;
  }
  return res;
}

int main(int argc, char *argv[])
{
  string curr = "19b91";

  while(1)
  {
    curr = getNextPNumber(curr);
    if (has17Consecutive1Bits(to_base10<unsigned long long, 17>(curr)))
    {
      cout << to_base10<unsigned long long, 17>(curr) << endl;
      cout << curr << endl;
      return 0;
    }
  }
  
  return 0;
}
