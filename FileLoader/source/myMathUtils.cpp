#include "FileLoader/myMathUtils.h"


//============================================================================
myMathUtils::myMathUtils()
{
}

//============================================================================
// Factorial of n
int myMathUtils::factorial(int n)
{
  if (n <= 1) {
    return(1);
  }
  else {
    n = n*factorial(n - 1);
  }
  return n;
}

//============================================================================
// Binomial coefficient
double myMathUtils::binomial_coeff(int n, int k)
{
  return factorial(n) / (factorial(k)*factorial(n - k));
}
