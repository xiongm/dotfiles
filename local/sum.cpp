#include <iostream>
#include <sstream>
#include <climits>

using namespace std;


// tail recursion optimization
int64_t sum_helper(unsigned int n, int64_t result = 0)
{
  if (n == 0)
  {
    return result;
  }
  return sum_helper(n - 1, result + n);
}

int64_t sum(int n)
{
  int sign = n > 0 ? 1 : -1;

  // sum_helper will only calculate the positive number
  // so res = sign * sum_helper(n)
  // if n > 0 then convert it to unsigned int
  // if n < 0 then convert it to unsigned int as well
  return sign * sum_helper(n > 0 ? (unsigned int) n : -((unsigned int)n)); 
}


int64_t no_tail_sum(int n)
{
  if (n == 0)
  {
    return 0;
  }

  if (n == INT_MIN)
  {
    return (sum(INT_MAX) + INT_MAX + 1) * -1;
  }
  if (n < 0)
  {
    return sum(0 - n) * -1;
  }
  return n + sum(n - 1);
}

bool valid(const char *s)
{
  while (*s != '\0')
  {
    char c = *s++;
    if (c == '+' || c == '-' || (c >= '0' && c <= '9')) continue;
    return false;
  }
  return true;
}


int main(int argc, char *argv[])
{

  for (int i = 1; i < argc; ++i)
  {
    if (valid(argv[i]))
    {
      int n = atoi(argv[i]);
      cout << "The sum of all integers between 0 and " << n << " is " << sum(n) << endl;
    } else
    {
      cout << argv[i] << " is not a number" << endl; 
    }
  }
  
  return 0;
}
