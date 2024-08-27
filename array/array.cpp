#include <cstddef> // size_t
#include <iostream>       
#include <stdexcept>    
#include <type_traits>  

template <typename T, size_t N>
class Array
{
public:
    Array() = default;

    template<typename... Tc>
    Array(Tc... list);

    template <size_t M>
    Array<T, N+M> concat(Array<T, M> const& other);

    template <typename... Ts>
    void set(Ts... list);

    T& operator[](size_t i)
    {
        return data[i];
    }
private:
    void set_helper(size_t i);
    
    template <typename First, typename... Rest>
    void set_helper(size_t i, First first, Rest... rest);

    T data[N];

};

template<typename T, size_t N>
template<typename... Tc>
Array<T, N>::Array(Tc... list)
: data{list...}
{
    std::cout << "Variadic constructor is called." << std::endl;
}

template<typename T, size_t N>
void Array<T, N>::set_helper(size_t){}

template<typename T, size_t N>
template <typename First, typename... Rest>
void Array<T, N>::set_helper(size_t i, First first, Rest... rest)
{    
    data[i] = first;
    set_helper(i+1, rest...);
}

template<typename T, size_t N>
template <typename... Ts>
void Array<T, N>::set(Ts... list)
{
    static_assert(sizeof...(list) <= N, "Too many elements...");
    static_assert((std::is_same_v<T, Ts> && ...), "Elements must be the same type.");
    set_helper(0, list...);
}

template <typename T, size_t N>
template <size_t M>
Array<T, N+M> Array<T, N>::concat(Array<T, M> const& other)
{
    Array<T, N+M> result;
    for (size_t i{0}; i < N; ++i)
    {
        result[i] = data[i];
    }
    for (size_t i{0}; i < M; ++i)
    {
        result[N + i] = other[i];
    }
    return result;
}

// Partial specialization
template<typename T>
class Array<T, 0>
{
public:
    static size_t size()
    {
        return 0;
    }
    T& operator[](size_t i)
    {
        throw std::out_of_range{"No elements"};
    }
};

// Full specialization
template<>
class Array<int, 0>
{
public:
    static size_t size()
    {
        return 0;
    }
    int& operator[](size_t i)
    {
        throw std::out_of_range{"No elements"};
    }
};

template <typename... Ts>
auto foo(Ts... data)
{
return ((data * data) + ...);
}

int main()
{
    Array<int, 3> arr{1, 2, 3};

    Array<int, 3> arr_2{};
    arr_2.set(4, 5, 6);

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "arr[1]: " << arr[1] << std::endl;
    std::cout << "arr[2]: " << arr[2] << std::endl;

    std::cout << foo(3, 4) << std::endl;

    return 1;
}