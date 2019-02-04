#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

ostream & operator << (ostream & strm, const vector<vector<int>> & rhs)
{
  for (auto i : rhs) {
    for (auto j : i) {
      strm << j;
    }
    strm << endl;
  }
  return strm;
}

int main(int argc, char *argv[])
{
  cout << "Please input 3 X 3 matrix with integers (seperated by whitespace): " << endl;
  {
    vector<vector<int>> inputs(3, vector<int>(3, 0));
    for (decltype(inputs.size()) i = 0; i < inputs.size(); i++)
    {
      std::string line;
      getline(cin, line);
      switch (i)
      {
        case 0:
          {
            istringstream is(line);
            inputs[i].assign(istream_iterator<int>(is), istream_iterator<int>());
          }
          break;
        case 1:
          {
            int x, y, z;
            istringstream(line) >> x >> y >> z;
            inputs[i][0] = x;
            inputs[i][1] = y;
            inputs[i][2] = z;
          }
          break;
        case 2:
          {
            istringstream is(line);
            // or back_inserter/front_inserter
            copy(istream_iterator<int>(is), istream_iterator<int>(), begin(inputs[i]));
          }
          break;
      }

    }

    cout << inputs;
  }

  cout << "Please input 3 X 3 matrix with integers (seperated by whitespace): " << endl;
  {
    vector<vector<int>> inputs(3, vector<int>(3, 0));
    for (decltype(inputs.size()) i = 0; i < inputs.size(); i++)
    {
      for (decltype(inputs[0].size()) j = 0; j < inputs[0].size(); j++)
      {
        int x;
        cin >> x;
        inputs[i][j]= x;
      }
      cin.ignore();
    }
    cout << inputs;
  }

  cout << "Please input 3 X 3 matrix with integers (seperated by comma): " << endl;
  {
    vector<vector<int>> inputs(3, vector<int>(3, 0));
    for (decltype(inputs.size()) i = 0; i < inputs.size(); i++)
    {
      switch (i)
      {
        case 0:
          {
            std::string line;
            getline(cin, line);
            auto it = begin(inputs[i]);
            istringstream ss(line);
            while (getline(ss, line, ','))
            {
              int x;
              istringstream(line) >> x;
              *it = x;
              advance(it, 1);
            }
          }
          break;
        case 1:
          {
            int x, y, z;
            cin >> x;
            cin.ignore(256,',');
            cin >> y;
            cin.ignore(256,',');
            cin >> z;
            inputs[i][0] = x;
            inputs[i][1] = y;
            inputs[i][2] = z;
          }
          break;
        case 2:
          {
            int x, y, z;
            char eater;
            cin >> x >> eater >> y >> eater >> z;
            inputs[i][0] = x;
            inputs[i][1] = y;
            inputs[i][2] = z;
          }
          break;
      }

    }

    cout << inputs;
  }

  return 0;
}
