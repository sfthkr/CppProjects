#include <iostream>

template<typename... Ts>
void print(Ts... args){

    ((std::cout<<args<<std::endl), ...);
}