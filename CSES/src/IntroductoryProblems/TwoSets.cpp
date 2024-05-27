// Your task is to divide the numbers 1,2,\ldots,n into two sets of equal sum.
// Input
// The only input line contains an integer n.
// Output
// Print "YES", if the division is possible, and "NO" otherwise.
// After this, if the division is possible, print an example of how to create the sets. First, print the number of elements in the first set followed by the elements themselves in a separate line, and then, print the second set in a similar way.
// Constraints

// 1 \le n \le 10^6

// Example 1
// Input:
// 7

// Output:
// YES
// 4
// 1 2 4 7
// 3
// 3 5 6
// Example 2
// Input:
// 6

// Output:
// NO

#include <print>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <ranges>
using namespace std;

namespace {

  class TwoSets {
  public:

    TwoSets(vector<int> set) : set_{set} {
      sum_ = accumulate(set.begin(), set.end(), 0);
    }



    int work() { //the problem condition is expanded 
      int minDiff = sum_;
      int size = set_.size();
      const int64_t power_size = pow(2, size); //exhaustive search of subsets!
      for (int64_t i = 0; i < power_size; i++) {
        int currSum = 0;
        for (int j = 0; j < size; j++)
          if (i & (1 << j)) {
            currSum += set_[j];
          }
        int diff = abs(sum_ - 2 * (currSum));
        if (diff == 0)
          return 0;
        minDiff = min(minDiff, diff);
      }
      return minDiff;
    }


  private:
    vector<int> set_;
    int sum_{};
  };



  void check(vector<int> set, int expected) {
    TwoSets twoSets(set);
    int result = twoSets.work();
    if (result != expected) {
      println("Error with expected = {}, result = {}", expected, result);
      throw exception("Error!");
    }
  }

}



void demo_TwoSets() {
  try {
    println("TwoSets started ...");
    int result;
    vector<int> set{4, 3, 1};
    TwoSets twoSets(set);
    result = twoSets.work();
    println("result = {}", result);

    //in release!
    //int n = 28;
    //vector<int> vec(n);
    //iota(std::begin(vec), std::end(vec), 1);
    //TwoSets bigSet(vec);
    //result = bigSet.work();
    //println("result = {}", result);

    check({1}, 1);
    check({1, 1}, 0);
    check({1, 2}, 1);
    check({2, 1}, 1);
    check({3, 1}, 2);
    check({1, 3}, 2);
    check({1, 3, 4}, 0);
    check({1, 3, 5}, 1);

    check({7, 3, 2, 2, 2, 2, 2}, 0); //!!!
    check({7, 3, 2, 2, 2, 2}, 0);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}