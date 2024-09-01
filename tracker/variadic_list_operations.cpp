#include <iostream>
#include <type_traits>

template<typename... Ts>
struct Pack{};

namespace v1{

namespace detail{

template<typename T>
bool contains(Pack<>){
    return false;
}

template<typename T, typename FirstT, typename... RestT>
bool contains(Pack<FirstT, RestT...> p){

    Pack<RestT...> restPack;
    if (std::is_same<T, FirstT>::value)
        return true;
    else
        return contains<T>(restPack);

}

template<int N, typename T>
int index_of(Pack<>){
    return -1;
}

template<int N, typename T, typename FirstT, typename... RestT>
int index_of(Pack<FirstT, RestT...> p){

    Pack<RestT...> restPack;
    if (std::is_same<T, FirstT>::value)
        return N;
    else
        return index_of<N+1, T>(restPack);

}

}

template<typename T, typename... Ts>
bool contains(Pack<Ts...> p){

    return detail::contains<T>(p);
}

template<typename T, typename... Ts>
int index_of(Pack<Ts...> p){

    return detail::index_of<0, T>(p);
}

}


inline namespace v2{

template<typename T, typename... Ts>
bool contains(Pack<Ts...> p){

    return (std::is_same_v<T, Ts> || ...);
}

template<typename T, typename... Ts>
int index_of(Pack<Ts...> p){

    int index = -1;
    if (((++index, std::is_same_v<T, Ts>) || ...))
        return index;

    return -1;
}


}


int main()
{
  using std::cout;
  using std::endl;
  Pack<int, double, long, float, std::string> p{};

  cout << contains<long>(p) << endl;
  cout << contains<char>(p) << endl;
  cout << endl;
  cout << index_of<int>(p) << endl;
  cout << index_of<float>(p) << endl;
  cout << index_of<char>(p) << endl;
}