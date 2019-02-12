#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
  int x;
  while (cin >> x && cin.ignore())
  {
    cout << x;
  }
  cout << endl;
  return 0;
}
