#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>

template <typename T, std::size_t dim = 3>
class Vector
{
public:

    template <typename U>
    Vector(U const& expression)
    {
        for (std::size_t i {0}; i < dim; ++i)
        {
            data[i] = expression[i];
        }
    }
    
    template <typename... Ts>
    Vector(std::initializer_list<T> list)
        : data { }
    {
        std::copy(list.begin(), list.end(), data.begin());
    }
    
    T  operator[](std::size_t i) const { return data[i]; }
    T& operator[](std::size_t i)       { return data[i]; }
    
private:
    
    std::array<T, dim> data { };
};

template <typename LHS, typename RHS>
class Vector_Sum
{
public:
    
    Vector_Sum(LHS const& lhs, RHS const& rhs)
        : lhs{lhs}, rhs{rhs} { }
    
    auto operator[](std::size_t i) const     
    { 
        return lhs[i] + rhs[i]; 
    }  
    
private:
    
    LHS const& lhs;
    RHS const& rhs;
    
};

template <typename LHS, typename RHS>
Vector_Sum<LHS, RHS> operator+(LHS const& lhs, RHS const& rhs)
{
    return { lhs, rhs };
}

template <typename LHS, typename RHS>
class Vector_Product
{
public:

    Vector_Product(LHS const& lhs, RHS const& rhs)
        : lhs{lhs}, rhs{rhs} { }

    auto operator[](std::size_t i) const     
    { 
        return lhs[i] * rhs; 
    }
    
private:

    LHS const& lhs;
    RHS const& rhs;

};

template <typename LHS, typename RHS>
Vector_Product<LHS, RHS> operator*(LHS const& lhs, RHS const& rhs)
{
    return { lhs, rhs };
}

int main()
{
    using Vec = Vector<double, 3>;
    
    Vec a { 1, 2 };
    Vec b { 3, 4 };
    Vec c { 5, 6 };
    Vec d { ((a + b) * 2.0 + c) };

    for (int i=0; i<2; ++i) {
        std::cout << d[i] << ", ";
    }
    std::cout << std::endl;
}