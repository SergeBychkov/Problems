//Given an array of n integers, your task is to find the maximum sum of values in a contiguous, nonempty subarray.
//Input
//The first input line has an integer n : the size of the array.
//The second line has n integers x_1, x_2, \dots, x_n: the array values.
//Output
//Print one integer : the maximum subarray sum.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//- 10 ^ 9 \le x_i \le 10 ^ 9
//
//Example
//Input :
//8
//- 1 3 - 2 5 3 - 5 2 2
//
//Output :
//  9
#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "random_utils.h"
#include "print_utils.h"
using namespace std;

namespace {
  class MaximumSubarraySumII {
  public:

    MaximumSubarraySumII(vector<int> vec) : vec_{vec} {}


    tuple<size_t, size_t, int> work(bool verbose = false) {
      int idxMax1{}, idxMax2{};
      int idx1{}, idx2{};
      int currSum{0}, maxSum{vec_[0]};
      size_t size = vec_.size();
      while (idx2 < size) {
        currSum += vec_[idx2];
        if (currSum >= maxSum) {
          maxSum = currSum;
          idxMax1 = idx1;
          idxMax2 = idx2;
        }
        if (currSum < 0) {
          idx1 = idx2 + 1;
          currSum = 0;
        }
        if (verbose) {
          println("idx1  = {}, idx2  = {}, currSum = {:3}", idx1, idx2, currSum);
          println("iMax1 = {}, iMax2 = {}, maxSum  = {:3}\n", idxMax1, idxMax2, maxSum);
        }
        idx2++;
      }
      return {idxMax1, idxMax2, maxSum};
    }



    tuple<size_t, size_t, int> solveByFullScan() { //slow, but correct!
      int idxMax1{}, idxMax2{};
      //int idx1{}, idx2{};
      int maxSum{vec_[0]};
      size_t size = vec_.size();
      for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j <= i; j++) {
          int currSum = 0;
          for (size_t k = j; k <= i; k++) {
            currSum += vec_[k];
          }
          if (currSum > maxSum) {
            maxSum = currSum;
            idxMax1 = j;
            idxMax2 = i;
          }
        }
      }
      return {idxMax1, idxMax2, maxSum};
    }


  private:
    vector<int> vec_;
  };



  void check(vector<int> vec, int expectedMaxSum) {
    MaximumSubarraySumII maxSubArr(vec);
    auto [idx1st, idx2nd, maxRes] = maxSubArr.work();
    if (maxRes != expectedMaxSum) {
      println("Error with result = {}, expected = {}", maxRes, expectedMaxSum);
      Print::printVector(vec, 4, 0, vec.size());
      throw exception("Error!");
    }
  }



  void autoCheck() {
    int size0 = 100;
    int nTimes = 1000;
    auto rnd = Random::createRandomIntGenerator(-100, 100);
    //auto rnd = Random::createRandomIntGenerator(-100, -1);
    for (size_t size = size0; size >= 10; size /= 10) {
      for (size_t i = 0; i < nTimes; i++) {
        vector<int> vec;
        vec.reserve(size);
        for (size_t k = 0; k < size; k++) {
          vec.push_back(rnd());
        }
        MaximumSubarraySumII maxSubArr(vec);
        auto [idx1, idx2, maxSum] = maxSubArr.solveByFullScan();
        check(vec, maxSum);
      }
    }
  }
}



void demo_MaximumSubarraySum() {
  try {
    println("MaximumSubarraySum started ...");
    //vector<int> vec{1, 1, -4, 1, 2, 3, -1, -1, 8, 8, -1};
    vector<int> vec{-28, 23, -13, 81, 40, -81, -88, 94, 34, 31};
    Print::printVector(vec, 4, 0, vec.size());

    MaximumSubarraySumII maxSubArr(vec);
    auto [idx1_correct, idx2_correct, maxSum_correct] = maxSubArr.solveByFullScan();
    auto [idx1, idx2, maxSum] = maxSubArr.work(true);
    println("correct result = ({}, {}), {}", idx1_correct, idx2_correct, maxSum_correct);
    println("result         = ({}, {}), {}\n", idx1, idx2, maxSum);

    autoCheck(); //in release with size0 = 1000; nTimes = 1000;

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}