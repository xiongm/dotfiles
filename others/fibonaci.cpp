#include <iostream>
#include <vector>
#include <limits> 
#include <cmath>
#include <unordered_set>

using namespace std;

void usage()
{
  cout << "fibonaci [number ...]" << endl;
}

// optimized 
auto is_prime_o = [](uintmax_t n) {
  if ( ( (!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3) )
    return (false);

  for( decltype(n)  k = 1; 36*k*k-12*k < n;++k)
    if ( (n % (6*k+1) == 0) || (n % (6*k-1) == 0) )
      return (false);
  return true;
};

// my prime 
auto my_is_prime = [](uintmax_t n) 
{
  if (n <= 1) return false;
  if ( ( (!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3) )
    return false;
  uintmax_t limit = pow(n, 0.5);
  for (decltype(limit)  i = 2; i <= limit; i++)
  {
    if (!(n % i)) return false;
  }
  return true;
};

auto fibonaci_prime(int count) 
{
  vector<uintmax_t> res;
  auto is_prime = my_is_prime;
  // fn_1 = f(n-1)
  // fn_2 = f(n-2)
  uintmax_t fn_1 = 1, fn_2 = 0;
  uintmax_t fn;
  if (count <= 1) return res;
  int n = 2;
  while (count > 0)
  {
    fn = fn_1 + fn_2;
   
    // if Fn is prime, then n is prime, except for when n == 4
    // so k is prime is a necessary condition
    // thus by checking k first, we can save a lot of time trying to
    // do primity check on fib, which is usually a large number
    // just math
    if ((n == 4? true : is_prime(n))  && is_prime(fn))
    //if (is_prime(fib))
    {
      count--;
      res.push_back(fn);
    }
    fn_2 = fn_1;
    fn_1 = fn;
    n++;
  }
  return res;
}

int main (int argc, char * argv[])
{
  if (argc < 2)
  {
    usage();
    return -1;
  }

  vector<int> input_num_seq;
  auto max_num = numeric_limits<int>::min();
  for (auto i = 1; i < argc; ++i)
  {
    auto num = atoi(argv[i]);
    input_num_seq.push_back(num);
    max_num = max(max_num, num);
  }

  if (!input_num_seq.empty())
  {
    vector<uintmax_t> res = fibonaci_prime(max_num);

    for(auto i : input_num_seq)
    {
      for (auto j = 0; j < i; j++)
      {
        cout << res[j] << " ";
      }
      cout << endl;
    }
  }

}
