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
  typedef typename Nth<typename LST::Tail, N-1>::result result;
};

template<typename LST>
struct Nth<LST, 0>
{
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

template<typename elem, typename LST>
struct Prepand
{
  typedef Lst<elem, LST> result;
};

template<typename elem, typename LST>
struct Append
{
  typedef typename Append<elem, typename LST::Tail>::result Next;
  typedef Lst< typename LST::Head, Next > result;
};

template<typename elem>
struct Append<elem, NIL>
{
  typedef Lst< elem > result;
};

template<typename elem, typename LST>
struct Position
{
  const static int result = Eq<elem, typename LST::Head>::result ? 0 : 1 +
    Position<elem, typename LST::Tail>::result;
};

template<typename elem>
struct Position<elem, NIL>
{
  const static int result = 0;
};

//can think of it as lambda expresion, that takes int type, and returns value
template <int N> struct Int{ static const int result = N; };

typedef Lst< Int<1>, Lst< Int<2>, Lst< Int<3> > > > OneTwoThree;
typedef Prepand< Int<-10>, OneTwoThree>::result MinusTenOneTwoThree;
typedef Append<Int<121>, OneTwoThree>::result OneTwoThree121;

int main()
{
  std::cout << "List length: " << Length<OneTwoThree>::result << std::endl;

  std::cout << "0-th element: " << Nth<OneTwoThree, 0>::result::result << std::endl;
  std::cout << "1-st element: " << Nth<OneTwoThree, 1>::result::result << std::endl;
  std::cout << "2-nd element: " << Nth<OneTwoThree, 2>::result::result << std::endl;

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

  if(Includes<Int<-10>, MinusTenOneTwoThree>::result &&
    Nth<MinusTenOneTwoThree, 0>::result::result == -10)
    std::cout << "Prepand works" << std::endl;

  if(Includes<Int<121>, OneTwoThree121>::result  &&
    Nth<OneTwoThree121, 3>::result::result == 121)
    std::cout << "Append works" << std::endl;

  std::cout << Position<Int<1>, OneTwoThree>::result << std::endl;
  std::cout << Position<Int<2>, OneTwoThree>::result << std::endl;
  std::cout << Position<Int<3>, OneTwoThree>::result << std::endl;
  std::cout << Position<Int<8>, OneTwoThree>::result << std::endl;
}
