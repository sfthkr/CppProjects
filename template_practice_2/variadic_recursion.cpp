#include <cstddef> // size_t
#include <iostream>       
#include <type_traits>  


void fun_helper() {}

template<typename First, typename... Rest>
void fun_helper(First first, Rest... rest){

    fun_helper(rest...);
}

template <typename... Ts>
void fun(Ts... list)
{
    fun_helper(list...);
}



int main ()
{

    fun(1, 2, 3);

    return -1;
}