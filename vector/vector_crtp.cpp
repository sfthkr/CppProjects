#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>

template <typename Expression>
class Vector_Base
{
public:
    auto operator[](std::size_t i) const;
};

template <typename Expression>
auto Vector_Base<Expression>::operator[](std::size_t i) const
{
  return static_cast<Expression const&>(*this)[i];
}

template <typename T, std::size_t dim = 3>
class Vector : public Vector_Base<Vector<T, dim>>
{
public:
    template <typename Expression>
    Vector(Vector_Base<Expression> const& other)
    {
        for (std::size_t i{0}; i < dim; ++i)
        {
            data[i] = other[i];
        }
    }
    
    Vector(std::initializer_list<T> list)
    {
        std::copy(list.begin(), list.end(), data.begin());
    }
    
    T  operator[](std::size_t i) const { return data[i]; }
    T& operator[](std::size_t i)       { return data[i]; }
            
private:
    std::array<T, dim> data { };
};

template <typename LHS, typename RHS>
class Vector_Sum : public Vector_Base<Vector_Sum<LHS, RHS>>
{
public:
    
    Vector_Sum(Vector_Base<LHS> const& lhs,
               Vector_Base<RHS> const& rhs)
        : lhs{lhs}, rhs{rhs} { }
    
    auto operator[](std::size_t i) const     
    { 
        return lhs[i] + rhs[i]; 
    }
    
private:
    
    Vector_Base<LHS> const& lhs;
    Vector_Base<RHS> const& rhs;
    
};

template <typename LHS, typename RHS>
Vector_Sum<LHS, RHS> operator+(Vector_Base<LHS> const& lhs,
                               Vector_Base<RHS> const& rhs)
{
    return { lhs, rhs };
}

// Notice that RHS is not a vector but a scalar
template <typename LHS, typename RHS>
class Vector_Product : public Vector_Base<Vector_Product<LHS, RHS>>
{
public:

    Vector_Product(Vector_Base<LHS> const& lhs,
                   RHS              const& rhs)
        : lhs{lhs}, rhs{rhs} { }

    auto operator[](std::size_t i) const     
    { 
        return lhs[i] * rhs; 
    }
    
private:

    Vector_Base<LHS> const& lhs;
    RHS              const& rhs;

};

// vector * scalar
template <typename LHS, typename RHS>
Vector_Product<LHS, RHS> operator*(Vector_Base<LHS> const& lhs, RHS const& rhs)
{
    return { lhs, rhs };
}

// scalar * vector
template <typename LHS, typename RHS>
Vector_Product<RHS, LHS> operator*(LHS const& lhs, Vector_Base<RHS> const& rhs)
{
    return { rhs, lhs };
}

int main()
{
    using Vec = Vector<double, 3>;
    
    Vec a { 1, 2 };
    Vec b { 3, 4 };
    Vec c { 5, 6 };
    Vec d { 0.5 * ((a + b) * 2.0 + c) };
}