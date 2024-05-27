//You are given an array of n integers.Your task is to calculate for each window of k elements, from left to right, the minimum total cost of making all elements equal.
//You can increase or decrease each element with cost x where x is the difference between the new and the original value.The total cost is the sum of such costs.
//Input
//The first input line contains two integers n and k: the number of elements and the size of the window.
//Then there are n integers x_1, x_2, \ldots, x_n: the contents of the array.
//Output
//Output n - k + 1 values : the costs.
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
//  2 2 5 7 7 1


#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  class SlidingWindowCost {
  public:

    SlidingWindowCost(vector<int> vec, int k) : vec_{vec}, k_{k} {}


    vector<int64_t> work() {
      vector<int64_t> result;
      vector<int> tempVec(k_);
      copy(vec_.begin(), vec_.begin() + k_, tempVec.begin());
      ranges::sort(tempVec);
      int lowSize = (k_ % 2 == 0) ? k_ / 2 : k_ / 2 + 1;
      int highSize = k_ - lowSize;
      multiset<int> low(tempVec.begin(), tempVec.begin() + lowSize);
      multiset<int> high(tempVec.begin() + lowSize, tempVec.end());
      int64_t lowSum = accumulate(low.begin(), low.end(), 0);
      int64_t highSum = accumulate(high.begin(), high.end(), 0);

      auto res = (k_ % 2 == 0) ? (highSum - lowSum) : highSum - lowSum + *low.rbegin();
      result.push_back(res);

      int vecSize = vec_.size();
      for (size_t i = 1; i < vecSize - k_ + 1; i++) {
        int mid = *low.rbegin();
        int add = vec_[i + k_ - 1];
        int del = vec_[i - 1];

        if (add <= mid && del <= mid) {
          low.insert(add);
          erase(low, del);
          lowSum += add - del;
        } else if (add > mid && del > mid) {
          high.insert(add);
          erase(high, del);
          highSum += add - del;
        } else if (add <= mid && del > mid) {
          low.insert(add);
          erase(high, del);
          int temp = *low.rbegin();
          high.insert(temp);
          erase(low, temp);
          lowSum += add - temp;
          highSum += temp - del;
        } else if (add > mid && del <= mid) {
          high.insert(add);
          erase(low, del);
          int temp = *high.begin();
          low.insert(temp);
          erase(high, temp);
          lowSum += temp - del;
          highSum += add - temp;
        } else {
          throw exception("Error in work() - cases!");
        }
        //println("low.size() = {}, high.size() = {}", low.size(), high.size());
        
        if (low.size() != lowSize || high.size() != highSize) {
          throw exception("Error in work() - sizes!");
        }

        res = (k_ % 2 == 0) ? (highSum - lowSum) : highSum - lowSum + *low.rbegin();
        result.push_back(res);
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



  void check(vector<int> vec, int k, vector<int64_t> expected) {
    SlidingWindowCost slidingWindowCost(vec, k);
    auto result = slidingWindowCost.work();
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
      SlidingWindowCost slidingWindowCost(vec, k);
      auto result = slidingWindowCost.work();
    }
  }
}



void demo_SlidingWindowCost() {
  try {
    println("demo_SlidingWindowCost started ...\n");

    vector<int> vec{2, 4, 3, 5, 8, 1, 2, 1};
    int k = 3;
    SlidingWindowCost slidingWindowCost(vec, k);
    auto result = slidingWindowCost.work();
    print("k = {}, vec: ", k); Print::printVector(vec, 3);
    print("result = "); Print::printVector(result, 3);

    check({2, 4, 3, 5, 8, 1, 2, 1}, 3, {2, 2, 5, 7, 7, 1});

    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}