//Given an array of n integers, your task is to count the number of subarrays having sum x.
//Input
//The first input line has two integers n and x: the size of the array and the target sum x.
//The next line has n integers a_1, a_2, \dots, a_n: the contents of the array.
//Output
//Print one integer : the required number of subarrays.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//- 10 ^ 9 \le x, a_i \le 10 ^ 9
//
//Example
//Input :
//5 7
//2 - 1 3 5 - 2
//
//Output :
//  2

#include <print>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include "random_utils.h"
#include "print_utils.h"
using namespace std;

namespace {
  class SubarraySumsII {
  public:

    SubarraySumsII(vector<int> vec, int64_t x) :vec_{vec}, x_{x} {}


    int work(bool verbose = false) {
      //https://github.com/the-hyp0cr1t3/CC/blob/master/CSES/Sorting%20and%20Searching/Subarray%20Sums%20II.cpp
      //https://usaco.guide/problems/cses-1661-subarray-sums-ii/solution
      int64_t result{}, currSum{};
      //map<int64_t, int> sums; // original code
      unordered_map<int, int> sums;
      sums[0] = 1;
      for (int i = 0; i < vec_.size(); i++) {
        currSum += vec_[i];
        result += sums[currSum - x_];
        sums[currSum]++;

        if (verbose) {
          Print::printMap(sums);
          println("i = {}, currSum = {}, curr-x_ = {}, result = {}", i, currSum, currSum - x_, result);
          println("--------------------------------------------------------------------------------\n");
        }
      }
      return result;
    }



    int workSerg(bool verbose = false) { //optimized(?), without unnessesary additions to map
      int64_t result{}, currSum{};
      int64_t curr_x_value{};
      unordered_map<int, int> sums;
      sums[0] = 1;
      for (int i = 0; i < vec_.size(); i++) {
        currSum += vec_[i];
        if (sums.contains(currSum - x_)) {
          result += sums[currSum - x_];
          curr_x_value = sums[currSum - x_];
        } else {
          curr_x_value = 0;
        }
        sums[currSum]++;

        if (verbose) {
          Print::printMap(sums);
          println("i = {}, vec_[i] = {}, currSum = {}, sums[currSum-x_ ({})] = {}, result = {}", i, vec_[i], currSum, currSum - x_, curr_x_value, result);
          println("--------------------------------------------------------------------------------");
        }
      }
      return result;
    }



    int workByCompleteSearch() { //slow - n*n*n
      int64_t result{};
      auto size = vec_.size();
      for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j <= i; j++) {
          int sum = 0;
          for (size_t k = j; k <= i; k++) {
            sum += vec_[k];
          }
          if (sum == x_)
            result++;
        }
      }
      return result;
    }


  private:
    vector<int> vec_;
    int64_t x_;
  };



  void check(vector<int> vec, int64_t x, int64_t expected) {
    SubarraySumsII josephusProblemII(vec, x);

    auto result = josephusProblemII.work();
    if (result != expected) {
      println("Error in work with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }

    result = josephusProblemII.workSerg();
    if (result != expected) {
      println("Error in workworkSerg with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }

    result = josephusProblemII.workByCompleteSearch();
    if (result != expected) {
      println("Error in work ByCompleteSearch with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }


  void autoCheck() {
    int nTests = 1'000;
    int size0 = 10'000;
    for (int i = 0; i < nTests; i++) {
      for (int size = size0; size >= 10; size /= 10) {
        auto vec = Random::getRandomIntVector(size, -10, 10);
        auto rnd = Random::createRandomIntGenerator(-10, 10);
        SubarraySumsII josephusProblemII(vec, rnd());
        auto result1 = josephusProblemII.work();
        auto result2 = josephusProblemII.workSerg();
        if (result1 != result2) {
          throw exception("Error in autoCheck!");
        }
      }
    }
  }



  void simpleDemo() {
    vector<int> vec{1, 2, 3, 3, 3, 6};
    int x = 6;

    print("x = {}, vec = ", x); Print::printVector(vec, 3); println("");
    SubarraySumsII josephusProblemII(vec, x);
    auto result = josephusProblemII.work(true);
    println("result work     = {}\n", result);
    result = josephusProblemII.workSerg(true);
    println("result workSerg = {}\n", result);
    result = josephusProblemII.workByCompleteSearch();
    println("result workByCompleteSearch = {}\n", result);
  }



  void demoHelper(vector<int> vec, int64_t x) {
    SubarraySumsII josephusProblemII(vec, x);
    auto result = josephusProblemII.workSerg(true);
    print("x = {}, vec  = ", x); Print::printVector(vec, 3);
    println("result workSerg = {}\n\n", result);
  }


  void learningDemo() {
    demoHelper({0, 0, 0}, 0);
    demoHelper({1, 1, 1}, 1);
    demoHelper({0, 1, 0, 1, 0}, 0);
    demoHelper({0, 0, 1, 0}, 0);
  }
}



void demo_SubarraySumsII() {
  try {
    println("demo_JosephusProblemII started ...\n");

    //simpleDemo();
    learningDemo();

    check({0}, 0, 1);
    check({0, 0}, 0, 3);
    check({0, 0, 0}, 0, 6);
    check({0, 0, 0, 0}, 0, 10);
    check({0, 0, 0, 1, 0}, 0, 7);
    check({0, 0, 0, 1, 0, 0}, 0, 9);

    check({1}, 1, 1);
    check({1, 1}, 1, 2);
    check({1, 1, 1}, 1, 3);

    check({-1, 0, 1}, 0, 2);
    check({1, -1, 1, -1}, 0, 4);

    check({-2, -1, 0, 1, 2}, 0, 3);
    check({2, -1, 3, 5, -2}, 7, 2);

    //autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}