#include <iostream>

struct NIL {
    typedef NIL Head;
    typedef NIL Tail;
};

template <typename H, typename T=NIL>
struct Lst
{
    typedef H Head;
    typedef T Tail;
};

template <typename LST>
struct Length
{
    static const unsigned int result = 1 + Length< typename LST::Tail >::result;
};

template <>
struct Length<NIL> {
    static const unsigned int result = 0;
};

template<typename LST, int N>
struct Nth
{
  //static const unsigned int result = Nth<typename LST::Tail, N-1>::result;
  typedef typename Nth<typename LST::Tail, N-1>::result result;
};

template<typename LST>
struct Nth<LST, 0>
{
  //static const unsigned int result = LST::Head::result;
  typedef typename LST::Head result;
};

template<typename X, typename Y>
struct Eq
{
  static const bool result = false;
};

template<typename X>
struct Eq<X,X>
{
  static const bool result = true;
};

template<typename elem, typename LST>
struct Includes
{
  const static bool result = Eq<typename LST::Head, elem>::result ||
   Includes<elem, typename LST::Tail>::result;
};

template<typename elem>
struct Includes<elem, NIL>
{
  const static bool result = false;
};

//can think of it as lambda expresion, that takes int type, and returns value
template <int N> struct Int{ static const int result = N; };

typedef Lst< Int<1>, Lst< Int<2>, Lst< Int<3> > > > OneTwoThree;

int main()
{
  std::cout << "List length: " << Length<OneTwoThree>::result << std::endl;

  std::cout << "0-th element: " << Nth<OneTwoThree, 0>::result::result << std::endl;
  std::cout << "1-st element: " << Nth<OneTwoThree, 1>::result::result << std::endl;
  std::cout << "2-nd element: " << Nth<OneTwoThree, 2>::result::result << std::endl;

  //std::cout << "2-nd element: " << Nth<OneTwoThree, 32>::result::result << std::endl;

  std::cout << "Includes 0: ";
  if(Includes<Int<0>, OneTwoThree>::result)
    std::cout << "yes" << std::endl;
  else
    std::cout << "no" << std::endl;
  std::cout << "Includes 1: ";
  if(Includes<Int<1>, OneTwoThree>::result)
    std::cout << "yes" << std::endl;
  else
    std::cout << "no" << std::endl;
  std::cout << "Includes 2: ";
  if(Includes<Int<2>, OneTwoThree>::result)
     std::cout << "yes" << std::endl;
  else
    std::cout << "no" << std::endl;
}
