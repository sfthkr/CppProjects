#include <string>
#include <iostream>

/*
  Put your code here
  
  Or even better, place it in another file
  and include that file.
 */

template <typename T>
int count();

template<typename T>
class Tracker: public T{

public:

    template<typename... P>
    Tracker(P&&... params)
    : T{std::forward<P>(params)...}
    {
        ++counter;
    }

    Tracker(const Tracker<T>& other)
    : T{other}
    {
      ++counter;
    }

    Tracker<T>& operator=(const Tracker<T>& other)
    {
      Tracker<T> tmp{other};
      return *this = std::move(tmp);
    }

    Tracker(Tracker<T>&&) = default;

    ~Tracker()
    {
        --counter;
    }

private:
    static unsigned counter;
    friend int count<T>();
};

template<typename T>
unsigned Tracker<T>::counter{0};


template <typename T>
int count(){
  return Tracker<T>::counter;
}



struct Hello_Worlder
{
  std::string get()
  {
    return "hello world!";
  }
};

/* The output should be:

0
str1 str2
hello world!
++++++++++
3
1
2

*/

int main()
{
  using std::cout;
  using std::endl;
  using std::string;

  cout << count<string>() << endl;
  
  Tracker<string> str1{};
  str1 += "str1";
  
  cout << count<string>() << endl;

  for (char c : str1)
  {
    cout << c;
  }
  
  Tracker<string> str2{"str2"};
  cout << " " << str2 << endl;

  Tracker<Hello_Worlder> hw{};
  cout << hw.get() << endl;

  {
    Tracker<string> str3(10u, '+');
    cout << str3 << endl;
    cout << count<string>() << endl;
  }
  cout << count<Hello_Worlder>() << endl;
  cout << count<string>() << endl;
  
}