//Your task is to count the number of ways to construct sum n by throwing a dice one or more times.Each throw produces an outcome between 1 and 6.
//For example, if n = 3, there are 4 ways:
//
//1 + 1 + 1
//1 + 2
//2 + 1
//3
//
//Input
//The only input line has an integer n.
//Output
//Print the number of ways modulo 10 ^ 9 + 7.
//Constraints
//
//1 \le n \le 10 ^ 6
//
//Example
//Input :
//3
//
//Output :
//  4

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "../Utils/print_utils.h"
using namespace std;

namespace {
  class DiceCombinations {
  public:

    DiceCombinations(int n) : n_{n}, results_{vector<int64_t>(n+2, -1)} {}


    int work() {
      int result{};
      results_[0] = 1;
      results_[1] = 1;
      results_[2] = 2;
      for (int i = 3; i <= n_; i++) {
        result = 0;
        for (int j = 1; j <= 6; j++) {
          if (i - j >= 0) {
            result += results_[i - j];
          }
        }
        results_[i] = result;
      }
      return results_[n_];
    }


  private:
    int n_;
    vector<int64_t> results_;
  };



  void check(int n, int expected) {
    DiceCombinations diceCombinations(n);
    auto result = diceCombinations.work();;
      if (result != expected) {
        println("Error with result = {}, expected = {}", result, expected);
        throw exception("Error!");
      }
  }
}



void demo_DiceCombinations() {
  try {
    println("demo_DiceCombinations started ...\n");

    DiceCombinations diceCombinations(4);
    auto result = diceCombinations.work();
    println("result = {}", result);

    check(1, 1);
    check(2, 2);
    check(3, 4);
    check(4, 8);
    check(5, 16);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}