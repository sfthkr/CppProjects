#include <type_traits>
#include <iostream>

namespace details
{ 
    // implement add_pointers function template here
    template<typename T, typename U, typename = std::enable_if_t<!std::is_pointer<U>::value>>
    T add_pointers_helper() {
      return T{};
    }

    template<typename T, typename U, typename = std::enable_if_t<std::is_pointer<U>::value>>
    auto add_pointers_helper(){
      return details::add_pointers_helper<T*, std::remove_pointer_t<U>>();
    }
}

template <typename T, typename U>
struct add_pointers
{
  using type = decltype(details::add_pointers_helper<T, U>());
};

template<class T>
void foo2(std::enable_if_t<std::is_integral<T>::value >) 
{
}

int main()
{
  static_assert(std::is_same_v<add_pointers<int, int>::type, int>, "int + int = int");
  static_assert(std::is_same_v<add_pointers<int, int*>::type, int*>, "int + int* = int*");
  static_assert(std::is_same_v<add_pointers<int*, int*>::type, int**>, "int* + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int*>::type, int***>, "int** + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int***>::type, int*****>, "int** + int*** = int*****");

  foo2<int>();
}