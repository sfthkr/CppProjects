struct false_type{
  static constexpr bool value{false};
};

struct true_type{
  static constexpr bool value{true};
};

// Implement is_const, is_pointer, is_array and is_const_pointer here
// is_const
template<typename T>
struct is_const : false_type{};

template<typename T>
struct is_const<const T> : true_type{};

// is_pointer
template<typename T>
struct is_pointer : false_type {}; 

template<typename T>
struct is_pointer<T*> : true_type {}; 

template<typename T>
struct is_pointer<T* const> : true_type {}; 

// is_array
template<typename T>
struct is_array : false_type {};

template<typename T, unsigned N>
struct is_array<T[N]> : true_type {};

// is_const_pointer
template<typename T>
struct is_const_pointer {
  static constexpr bool value {is_const<T>::value && is_pointer<T>::value};
};



int main()
{ 
  static_assert(is_const<int const>::value, "is_const failed for 'int const'");
  static_assert(is_const<int* const>::value, "is_const failed for 'int* const'");
  static_assert(!is_const<int>::value, "is_const failed for 'int'");
  static_assert(!is_const<int const*>::value, "is_const failed for 'int const*'");

  static_assert(is_pointer<int*>::value, "is_pointer failed for 'int*'");
  static_assert(is_pointer<int const*>::value, "is_pointer failed for 'int const*'");
  static_assert(is_pointer<int* const>::value, "is_pointer failed for 'int* const'");
  static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");
  static_assert(!is_pointer<int const>::value, "is_pointer failed for 'int'");

  static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
  static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
  static_assert(!is_array<int>::value, "is_array failed for 'int'");

  static_assert(is_const_pointer<int* const>::value, "is_const_pointer failed for 'int* const'");
  static_assert(!is_const_pointer<int*>::value, "is_const_pointer failed for 'int*'");
  static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
  static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");

}