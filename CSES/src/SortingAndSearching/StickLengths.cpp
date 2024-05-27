//There are n sticks with some lengths.Your task is to modify the sticks so that each stick has the same length.
//You can either lengthen and shorten each stick.Both operations cost x where x is the difference between the new and original length.
//What is the minimum total cost ?
//Input
//The first input line contains an integer n : the number of sticks.
//Then there are n integers : p_1, p_2, \ldots, p_n: the lengths of the sticks.
//Output
//Print one integer : the minimum total cost.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le p_i \le 10 ^ 9
//
//Example
//Input :
//5
//2 3 1 5 2
//
//Output :
//  5

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {
  class StickLengths {
  public:

    StickLengths(vector<int> sticks) : sticks_{sticks} {
      ranges::sort(sticks_);
    }


    int work() {
      int result{};
      size_t size = sticks_.size();
      if (size == 1)
        return 0;
      int pairsCnt = size / 2;
      for (size_t i = 0; i < pairsCnt; i++) {
        result += sticks_[size - 1 - i] - sticks_[i];
      }
      return result;
    }


  private:
    vector<int> sticks_;
  };



  void check(vector<int> sticks, int expected) {
    StickLengths stickLengths(sticks);
    int result = stickLengths.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_StickLengths() {
  try {
    println("demo_StickLengths started ...");
    
    vector<int> sticks{2, 3, 1, 5, 2};
    StickLengths stickLengths(sticks);
    auto result = stickLengths.work();
    println("result = {}", result);

    check({1}, 0);
    check({1, 1, 2}, 1);
    check({1, 1, 1, 1, 10}, 9);
    check({2, 2, 2, 1}, 1);
    check({2, 2, 2, 2, 1}, 1);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}