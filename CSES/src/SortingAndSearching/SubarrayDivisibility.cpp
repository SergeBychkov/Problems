//Given an array of n integers, your task is to count the number of subarrays where the sum of values is divisible by n.
//Input
//The first input line has an integer n : the size of the array.
//The next line has n integers a_1, a_2, \dots, a_n: the contents of the array.
//Output
//Print one integer : the required number of subarrays.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//- 10 ^ 9 \le a_i \le 10 ^ 9
//
//Example
//Input :
//5
//3 1 2 7 4
//
//Output :
//  1

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  class SubarrayDivisibility {
  public:

    //SubarrayDivisibility(vector<int> vec) :vec_{vec}, n_{(int)vec.size()} {} //original task condition
    SubarrayDivisibility(vector<int> vec, int n) :vec_{vec}, n_{n} {}          //generalization of task condition


    int work(bool verbose = false) {
      int result{}, currRem{};
      unordered_map<int, int> rems; //remainder of the division
      rems[0] = 1;
      int currSum = 0;
      for (int i = 0; i < vec_.size(); i++) {
        currSum += vec_[i];
        currRem = currSum % n_;

        if (rems.contains(currRem)) {
          result += rems[currRem];
        }
        rems[currRem]++;

        if (verbose) {
          Print::printMap(rems);
          println("i = {}, result = {}", i, result);
          println("--------------------------------------------------------------------------------\n");
        }
      }
      return result;
    }



  private:
    vector<int> vec_;
    int n_;
  };



  void check(vector<int> vec, int n, int expected) {
    SubarrayDivisibility subarrayDivisibility(vec, n);
    auto result = subarrayDivisibility.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      print("n = {}, vec:", n); Print::printVector(vec, 3);
      throw exception("Error!");
    }
  }


  void simpleDemo(vector<int> vec, int n) {
    SubarrayDivisibility subarrayDivisibility(vec, n);
    auto result = subarrayDivisibility.work(true);
    print("n = {}, vec:", n); Print::printVector(vec, 3);
    println("result = {}\n", result);
  }



  void demoHelper(vector<int> vec, int n) {
    SubarrayDivisibility subarrayDivisibility(vec, n);
    auto result = subarrayDivisibility.work(true);
    print("n = {}, vec  = ", n); Print::printVector(vec, 3);
    println("result work = {}\n\n", result);
  }


  void learningDemo() {
    demoHelper({5, 5, 5}, 5);
    demoHelper({1, 1, 1}, 1);
    demoHelper({1, 2, 3}, 3);
    demoHelper({3, 1, 2, 7, 4, 5, 1}, 5);
    //demoHelper({0, 0, 1, 0}, 0);
  }

}



void demo_SubarrayDivisibility() {
  try {
    println("demo_SubarrayDivisibility started ...\n");

    //simpleDemo({5, 5, 5}, 5);
    learningDemo();
    
    //return;

    check({5}, 5, 1);
    check({5, 5}, 5, 3);
    check({5, 5, 5}, 5, 6);
    check({2, 5}, 5, 1);
    check({1, 2, 3}, 5, 1);
    check({1, 2, 3, 5}, 5, 3);
    check({1, 2, 3, 5, 4}, 5, 4);

    check({3, 1, 2, 7, 4}, 5, 1);
    check({3, 1, 2, 7, 4, 5}, 5, 2);
    check({3, 1, 2, 7, 4, 5, 1}, 5, 4);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}