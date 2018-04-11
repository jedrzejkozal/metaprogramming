#include <iostream>

template <int N, int D>
struct Frak
{
        static const long Num = N;
        static const long Den = D;
};

template <int N, typename F>
struct ScalarMultiplication
{
    typedef Frak<N*F::Num, N*F::Den> result;
};

template <int X, int Y>
struct MCD
{
        static const long result = MCD<Y, X % Y>::result;
};

template <int X>
struct MCD<X, 0>
{
        static const long result = X;
};

template <class F>
struct Simpl
{
        static const long mcd = MCD<F::Num, F::Den>::result;
        typedef Frak< F::Num / mcd, F::Den / mcd > result;
};

template <typename X1, typename Y1>
struct SameBase
{
    typedef typename ScalarMultiplication< Y1::Den, X1>::result X;
    typedef typename ScalarMultiplication< X1::Den, Y1>::result Y;
};

template <typename X, typename Y>
struct Sum
{
    typedef SameBase<X, Y> B;
    static const long Num = B::X::Num + B::Y::Num;
    static const long Den = B::Y::Den; // == B::X::Den
    typedef typename Simpl< Frak<Num, Den> >::result result;
};

int main()
{
  std::cout << Sum<Frak<1,3>, Frak<1,4> >::result::Num << "/" <<
  Sum<Frak<1,3>, Frak<1,4> >::result::Den << std::endl;
}
