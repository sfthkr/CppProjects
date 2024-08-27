#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

/*
  Your code here
 */
template<typename T>
using Func_T = T (*)(const T&, const T&);

template<typename T>
T default_sum_func(const T& lhs, const T& rhs)
{
    return lhs + rhs;
}

template <typename Input_T, size_t N>
Input_T reduce (Input_T const (&inArray)[N], Input_T initVal = {}, Func_T<Input_T> func = default_sum_func)
{
    Input_T result{initVal};

    for (const auto& elem: inArray){
        result = func(result, elem);
    }

    return result;
}

double multiply(double const& lhs, double const& rhs)
{
    return lhs * rhs;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1,2,3,4,5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}