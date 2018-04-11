#include <iostream>

template<int N>
struct Factorial
{
  const static int result = N * Factorial<N-1>::result;
};

template<>
struct Factorial<0>
{
  const static int result = 1;
};

int main()
{
  std::cout << Factorial<4>::result << std::endl;
}
