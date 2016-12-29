#include <iostream>

using namespace std;

template<class T>
class Singleton
{
public:
  static T & instance()
  {
    // thread safe, always available
    static T * instance = new T();
    return *instance;
  }
private:
  Singleton() {}
};

/*
template<class T>
T * Singleton<T>::instance_ = nullptr
*/
struct Dummy
{
  int get() const
  {
    return 1;
  }
};

int main(int argc, char *argv[])
{
  cout << Singleton<Dummy>::instance().get() << endl;
  return 0;
}
