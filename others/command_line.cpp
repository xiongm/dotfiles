#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{

  if (argc < 2) {
    return -1;
  }

  vector<string> args;
  copy_if(argv + 1, argv + argc, back_inserter(args), [](const char * a ) { return *a != '-';});

  for (auto & arg : args)
  {
    int x;
    if (istringstream(arg) >> x && x > 0) {
      cout << "you entered " << x << endl;

    } else {
      cout << arg << " is not a valid number" << endl;
    }
  }

  return 0;
}
