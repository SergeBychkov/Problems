//You are given an array of n integers.Your task is to calculate the median of each window of k elements, from left to right.
//The median is the middle element when the elements are sorted.If the number of elements is even, there are two possible medians and we assume that the median is the smaller of them.
//Input
//The first input line contains two integers n and k: the number of elements and the size of the window.
//Then there are n integers x_1, x_2, \ldots, x_n: the contents of the array.
//Output
//Print n - k + 1 values : the medians.
//Constraints
//
//1 \le k \le n \le 2 \cdot 10 ^ 5
//1 \le x_i \le 10 ^ 9
//
//Example
//Input :
//8 3
//2 4 3 5 8 1 2 1
//
//Output :
//  3 4 5 5 2 1

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  class SlidingWindowCost {
  public:

    SlidingWindowCost(vector<int> vec, int k) : vec_{vec}, k_{k} {}


    vector<int> work() {
      vector<int> result, tempVec(k_);
      copy(vec_.begin(), vec_.begin() + k_, tempVec.begin());
      ranges::sort(tempVec);
      int lowSize = (k_ % 2 == 0) ? k_ / 2 : k_ / 2 + 1;
      int highSize = k_ - lowSize;
      multiset<int> low(tempVec.begin(), tempVec.begin() + lowSize);
      multiset<int> high(tempVec.begin() + lowSize, tempVec.end());
      result.push_back(*low.rbegin());

      int vecSize = vec_.size();
      for (size_t i = 1; i < vecSize - k_ + 1; i++) {
        int mid = *low.rbegin();
        int add = vec_[i + k_ - 1];
        int del = vec_[i - 1];

        if (add <= mid && del <= mid) {
          low.insert(add);
          erase(low, del);
        } else if (add > mid && del > mid) {
          high.insert(add);
          erase(high, del);
        } else if (add <= mid && del > mid) {
          low.insert(add);
          erase(high, del);
          int temp = *low.rbegin();
          high.insert(temp);
          erase(low, temp);
        } else if (add > mid && del <= mid) {
          high.insert(add);
          erase(low, del);
          int temp = *high.begin();
          low.insert(temp);
          erase(high, temp);
        } else {
          throw exception("Error in work() - cases!");
        }
        //println("low.size() = {}, high.size() = {}", low.size(), high.size());
        if (low.size() != lowSize || high.size() != highSize) {
          throw exception("Error in work() - sizes!");
        }
        result.push_back(*low.rbegin());
      }
      return result;
    }


  private:

    void erase(multiset<int>& map, int value) {
      auto pos = map.find(value);
      if (pos != map.end())
        map.erase(pos);
      else
        throw exception("Item not found!");
    }


    vector<int> vec_;
    int k_;
  };



  void check(vector<int> vec, int k, vector<int> expected) {
    SlidingWindowCost slidingWindowMedian(vec, k);
    auto result = slidingWindowMedian.work();
    if (result != expected) {
      print("Error with result:"); Print::printVector(result, 3);
      print("expected         :"); Print::printVector(expected, 3);
      throw exception("Error!");
    }
  }



  void autoCheck() {
    int size = 1000;
    auto vec = Random::getRandomIntVector(size, -100, 100);
    for (size_t k = 2; k < 100; k++) {
      SlidingWindowCost slidingWindowMedian(vec, k);
      auto result = slidingWindowMedian.work();
    }
  }
}



void demo_SlidingWindowMedian() {
  try {
    println("demo_SlidingWindowMedian started ...\n");

    vector<int> vec{2, 4, 3, 5, 8, 1, 2, 1};
    int k = 3;
    SlidingWindowCost slidingWindowMedian(vec, k);
    auto result = slidingWindowMedian.work();
    print("k = {}, vec: ", k); Print::printVector(vec, 3);
    print("result = "); Print::printVector(result, 3);

    check({2, 4, 3, 5, 8, 1, 2, 1}, 3, {3, 4, 5, 5, 2, 1});

    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}