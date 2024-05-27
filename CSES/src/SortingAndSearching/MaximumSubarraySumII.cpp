//Given an array of n integers, your task is to find the maximum sum of values in a contiguous subarray with length between a and b.
//Input
//The first input line has three integers n, a and b: the size of the array and the minimum and maximum subarray length.
//The second line has n integers x_1, x_2, \dots, x_n: the array values.
//Output
//Print one integer : the maximum subarray sum.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le a \le b \le n
//- 10 ^ 9 \le x_i \le 10 ^ 9
//
//Example
//Input :
//8 1 2
//- 1 3 - 2 5 3 - 5 2 2
//
//Output :
//  8

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

    MaximumSubarraySumII(vector<int> vec, int a, int b) : vec_{vec}, a_{a}, b_{b} {}


    tuple<size_t, size_t, int> work(bool verbose = false) {
      int idxMax1{}, idxMax2{};
      int idx1{}, idx2{};
      int currSum{0}, maxSum{vec_[0]};
      size_t size = vec_.size();
      for (int idx2 = 0; idx2 < size; idx2++) {
        if (idx2 - idx1 + 1 < a_) {
          continue;
        }
        if (idx2 - idx1 + 1 > b_) {
          idx1 = idx2 + 1 - b_;
          currSum -= vec_[idx1 - 1];
        }

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
          if (currSum > maxSum && (i - j + 1 >= a_) && (i - j + 1 <= b_)) {
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
    int a_;
    int b_;
  };



  void check(vector<int> vec, int a, int b, int expectedMaxSum) {
    MaximumSubarraySumII maximumSubarraySumII(vec, a, b);
    auto [idx1st, idx2nd, maxRes] = maximumSubarraySumII.work();
    if (maxRes != expectedMaxSum) {
      println("Error with result = {}, expected = {}", maxRes, expectedMaxSum);
      Print::printVector(vec, 4, 0, vec.size());
      throw exception("Error!");
    }
  }
}


void demo_MaximumSubarraySumII() {
  try {
    println("demo_MaximumSubarraySumII started ...");

    vector<int> vec{-1, 3, -2, 5, 3, -5, 2, 2};
    int a = 1, b = 2;
    Print::printVector(vec, 4, 0, vec.size());
    MaximumSubarraySumII maximumSubarraySumII(vec, a, b);
    auto [idx1_correct, idx2_correct, maxSum_correct] = maximumSubarraySumII.solveByFullScan();
    auto [idx1, idx2, maxSum] = maximumSubarraySumII.work(true);
    println("correct result = ({}, {}), {}", idx1_correct, idx2_correct, maxSum_correct);
    println("result         = ({}, {}), {}\n", idx1, idx2, maxSum);

    check({-1, 3, -2, 5, 3, -5, 2, 2}, 1, 2, 8);
    check({-1, 3, -2, 5, 3, -5, 2, 2}, 1, 4, 9);
    check({-1, 3, -2, 5, 3, -5, 2, 2}, 1, 1, 5);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}