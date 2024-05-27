//Your task is to count the number of ways numbers 1, 2, \ldots, n can be divided into two sets of equal sum.
//For example, if n = 7, there are four solutions :
//
//\{1, 3, 4, 6\} and \{2, 5, 7\}
//\{1, 2, 5, 6\} and \{3, 4, 7\}
//\{1, 2, 4, 7\} and \{3, 5, 6\}
//\{1, 6, 7\} and \{2, 3, 4, 5\}
//
//Input
//The only input line contains an integer n.
//Output
//Print the answer modulo 10 ^ 9 + 7.
//Constraints
//
//1 \le n \le 500
//
//Example
//Input :
//7
//
//Output :
//  4

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  class TwoSetsII {
  public:

    TwoSetsII(int n) : n_{n} {}


    int64_t work(bool verbose = false) {
      int maxSum = (n_ + 1) * n_ / 2 / 2;
      if (maxSum % 2 != 0)
        return 0;
      if (verbose) {
        for (size_t i = 0; i <= maxSum; i++) {
          print("{:3}", i);
        }
        println("\n----------------------------------------------------------------");
      }

      vector<int64_t> vec(maxSum + 1, 0);
      vec[0] = 1; vec[1] = 1;
      int currMaxIdx = 1;
      for (int i = 2; i <= n_; i++) {
        for (int j = currMaxIdx; j >= 0; j--) {
          if (vec[j] != 0) {
            if (i + j <= maxSum)
              vec[i + j] += vec[j];
          }
        }
        currMaxIdx += i;
        if (currMaxIdx > maxSum)
          currMaxIdx = maxSum;
        if (verbose) {
          println("i = {}", i);
          Print::printVector(vec, 3, 0, maxSum + 1);
        }
      }
      return vec[maxSum] / 2;
    }



  private:
    int n_;
  };



  void check(int expected) {
    //TwoSetsII qqq;
    //auto result = qqq.work();
    //if (result != expected) {
    //  println("Error with result = {}, expected = {}", result, expected);
    //  throw exception("Error!");
    //}
  }
}



void demo_TwoSetsII() {
  try {
    println("demo_TwoSetsII started ...\n");

    TwoSetsII twoSetsII(7);
    auto result = twoSetsII.work(true);
    println("result = {}", result);

    //check(100);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}