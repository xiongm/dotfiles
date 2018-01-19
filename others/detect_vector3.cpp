#include <type_traits>
#include <theme/mpl/detection.hpp>
#include <theme/mpl/static_if.hpp>
#include <vector>
#include <iostream>

template <typename>
struct is_vector  : std::false_type {};

template <typename T>
struct is_vector< std::vector<T> > : std::true_type {};

template <typename T>
using data_t = decltype(std::declval<T>().data);

struct Foo { int data; };
struct Bar { std::vector<int> data; };
struct Dummy { };

template <typename T>
void handle_object(T & obj)
{
  using namespace theme::mpl;
  static_if(is_detected<data_t,T>())
  .then([](auto & obj){
    static_if(is_vector<data_t<T>>())
    .then([] (auto & ) {
       std::cout << "has vector data" << std::endl;
    })
    .else_([](auto & ) {
      std::cout << "has non vector data" << std::endl;
    })(obj);
  })
  .else_([](auto &){
     std::cout << "has no data" << std::endl;
  })(obj);
}

int main()
{
  Foo foo;
  Bar bar;
  Dummy dummy;

  handle_object(foo);
  handle_object(bar);
  handle_object(dummy);

  return 0;
}



