#include <type_traits>
#include <theme/mpl/detection.hpp>
#include <vector>

#include <iostream>

template <typename>
struct is_vector  : std::false_type {};

template <typename T>
struct is_vector< std::vector<T> > : std::true_type {};

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
void handle_object(T & , std::enable_if_t< has_data_v<T> && is_data_vector_v<T> > * = nullptr)
{
  std::cout << "has vector data" << std::endl;
}

template <typename T>
void handle_object(T & , std::enable_if_t< has_data_v<T> && !is_data_vector_v<T> > * = nullptr)
{
  std::cout << "has non vector data" << std::endl;
}

template <typename T>
void handle_object(T & , std::enable_if_t< !has_data_v<T> > * = nullptr)
{
  std::cout << "has no data" << std::endl;
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



