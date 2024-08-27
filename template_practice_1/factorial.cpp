#include <iostream>

using namespace std;

/*
  Your code here
 */
template<unsigned long long val>
unsigned long long factorial(){
    return val*factorial<val-1>();
}

template<>
unsigned long long factorial<0>()
{ return 1; }

template<>
unsigned long long factorial<1>()
{ return 1; }

int main()
{
    cout << factorial<0>() << endl;
    cout << factorial<1>() << endl;
    cout << factorial<5>() << endl;
    cout << factorial<20>() << endl;
}