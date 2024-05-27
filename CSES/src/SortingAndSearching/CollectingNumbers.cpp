//You are given an array that contains each number between 1 \dots n exactly once.Your task is to collect the numbers from 1 to n in increasing order.
//On each round, you go through the array from left to right and collect as many numbers as possible.What will be the total number of rounds ?
//Input
//The first line has an integer n : the array size.
//The next line has n integers x_1, x_2, \dots, x_n: the numbers in the array.
//Output
//Print one integer : the number of rounds.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//
//Example
//Input :
//5
//4 2 1 5 3
//
//Output :
//  3

#include <print>
#include <vector>
#include <list>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {
  class CollectingNumbers {
  public:

    CollectingNumbers(const vector<int>& vec) {
      for (int x : vec) {
        list_.push_back(x);
      }
    }


    int work() {
      int result{};
      int currItem = 1;
      while (!list_.empty()) {
        for (auto it = list_.begin(); it != list_.end();) {
          if (*it == currItem) {
            it = list_.erase(it);
            currItem++;
          } else {
            it++;
          }
        }
        result++;
      }
      return result;
    }


  private:
    list<int> list_;
  };



  void check(vector<int> vec, int expected) {
    CollectingNumbers collectingNumbers(vec);
    auto result = collectingNumbers.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }


}



void demo_CollectingNumbers() {
  try {
    println("demo_CollectingNumbers started ...");

    vector<int> vec{4, 2, 1, 5, 3}; //expected = 3
    CollectingNumbers collectingNumbers(vec);
    auto result = collectingNumbers.work();;
    println("result = {}", result);

    check({1}, 1);
    check({1, 2}, 1);
    check({2, 1}, 2);
    check({5, 4, 3, 2, 1}, 5);
    check({4, 2, 1, 5, 3}, 3);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}