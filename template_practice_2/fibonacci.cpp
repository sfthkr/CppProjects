#include <cassert>

template<unsigned N>
class Fibonacci {
public:
    static constexpr unsigned value{Fibonacci<N-1>::value + Fibonacci<N-2>::value};
};

template<>
class Fibonacci<0> {
public:
    static constexpr unsigned value{0};
};

template<>
class Fibonacci<1> {
public:
    static constexpr unsigned value{1};
};


int main()
{
  assert(Fibonacci<0>::value == 0);
  assert(Fibonacci<1>::value == 1);
  assert(Fibonacci<5>::value == 5);
  assert(Fibonacci<10>::value == 55);
  assert(Fibonacci<12>::value == 144);
}