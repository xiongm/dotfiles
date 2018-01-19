#include <iostream>
#include <theme/mpl/detection.hpp>


template <typename T>
using do_stuff_template_t = decltype(std::declval<T>().template do_stuff_template<T>());

template <typename T>
constexpr bool has_do_stuff_template_v = theme::mpl::is_detected_v<do_stuff_template_t, T>;


template <typename T>
struct HasTemplate
{
  template <typename U, void (U::*)()> struct SFINAE {};
  template <typename U> static char Test(SFINAE<U, &U::template do_stuff_template<int>>*);
  //template <typename U> static char Test(SFINAE<U, &U::do_stuff>*);
  template <typename U> static int Test(...);
  static const bool Has = sizeof(Test<T>(0)) == sizeof(char);
};
using namespace std;
template <typename T>
class Foo
{
  public:
    void do_stuff() {
      cout << "do stuff" << endl;
    }

    template <typename U>
    void do_stuff_template(U ) {
      cout << "do stuff template" << endl;
    }
};

template class Foo<int>;

template void Foo<int>::do_stuff_template<int>(int);


template <typename T>
void handle(T & t, std::true_type)
{
  cout << "yes" << endl;
}

template <typename T>
void handle(T & t, std::false_type)
{
  cout << "no" << endl;
}


template <typename T>
void handle (T & t)
{
  handle(t, std::integral_constant<bool, HasTemplate<T>::Has>());
}
int main(int argc, char *argv[])
{
  Foo<int> a;
  a.do_stuff_template(1);
  handle(a);
  //static_assert(has_do_stuff_template_v< Foo<int>>, "fail");
  return 0;
}
