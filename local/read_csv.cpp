#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <sstream>

using namespace std;

struct Data
{
  string symbol;
  double price;
  bool is_open;

  Data(string symbol, double price, bool is_open)
    :symbol(std::move(symbol)), price(price), is_open(is_open)
  {

  }
  
  friend ostream & operator<<(ostream & os, const Data & data)
  {
    os << data.symbol << "," << data.price << "," << data.is_open;
    return os;
  }
};

class Solution
{
public:
  Solution(const char * file_name)
  {
    init(file_name);
  }

  void init(const char * file_name)
  {
    ifstream ifs(file_name);
    if (ifs.is_open())
    {
      string line;
      while (getline(ifs, line))
      {
        if (!line.empty())
        {
          istringstream iss(line);
          string symbol;
          double price;
          bool is_open;
          getline(iss, symbol, ',');
          iss.ignore();
          iss >> price;
          iss.ignore();
          iss >> is_open;
          data_.emplace_back(symbol, price, is_open);
        }
      }
    }

  }

  vector<Data> data_;
};

void usage()
{
  cout << "read_csv file_name" << endl;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    usage();
    return -1;
  }
  Solution solution(argv[1]);
  
  for (auto i : solution.data_)
  {
    cout << i << endl;
  }
  return 0;
}
