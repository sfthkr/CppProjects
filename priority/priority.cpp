#include <utility>
#include <iostream>

namespace detail{

template<typename T>
auto get_priority_helper(T&& t, int, int, int) -> decltype(t.first()) {
    return t.first();
}

template<typename T>
auto get_priority_helper(T&& t, long, int, int) -> decltype(t.second()) {
    return t.second();
}

template<typename T>
auto get_priority_helper(T&& t, long, long, int) -> decltype(t.third()) {
    return t.third();
}

template <typename T>
int get_priority_helper(T&&, long, long, long)
{
    return 4;
}

}


template <typename T>
auto get_priority(T&& t)
{
  /* TODO: implement */
  return detail::get_priority_helper(std::forward<T>(t), 0, 0, 0);
}

struct X
{
  int first() const { return 1; }
};

struct Y
{
  int second() const { return 2; }
};

struct Z
{
  int third() const { return 3; }
};

struct XY
{
  int first() const { return 1; }
  int second() const { return 2; }
};

struct XZ
{
  int first() const { return 1; }
  int third() const { return 3; }
};

struct YZ
{
  int second() const { return 2; }
  int third() const { return 3; }
};

struct XYZ
{
  int first() const { return 1; }
  int second() const { return 2; }
  int third() const { return 3; }
};

int main()
{
  using std::cout;
  using std::endl;
  
  cout << get_priority(X{}) << endl
       << get_priority(Y{}) << endl
       << get_priority(Z{}) << endl
       << get_priority(XY{}) << endl
       << get_priority(XZ{}) << endl
       << get_priority(YZ{}) << endl
       << get_priority(XYZ{}) << endl
       << get_priority(5) << endl;
}