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
constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>
using data_t = decltype(std::declval<T>().data);


template <typename T>
constexpr bool has_data_v = theme::mpl::is_detected_v<data_t, T>;

template <typename T>
constexpr bool is_data_vector_v = is_vector<data_t<T>>::value;

struct Foo { int data; };

struct Bar { std::vector<int> data; };

struct Dummy { };


template <typename T>
struct Base
{

template <typename U = T>
void handle_object(U * = nullptr)
{
  using namespace theme::mpl;
  static_if(is_vector<data_t<U>>())
  .then([this] () {
    this->data.data = {1, 2, 3};
    //for (auto i : this->data.data)
    //{
      //std::cout << i << std::endl;
    //}
  })
  .else_([this]() {
    //this->data.data = 1;
    //std::cout << this->data.data << std::endl;
  })();
}

T data;
};

int main()
{
  Base<Foo> f;
  Base<Bar> b;
  f.handle_object();
  b.handle_object();


  return 0;
}



