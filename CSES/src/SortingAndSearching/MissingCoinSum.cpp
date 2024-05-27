//You have n coins with positive integer values.What is the smallest sum you cannot create using a subset of the coins ?
//Input
//The first input line has an integer n : the number of coins.
//The second line has n integers x_1, x_2, \dots, x_n: the value of each coin.
//Output
//Print one integer : the smallest coin sum.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le x_i \le 10 ^ 9
//
//Example
//Input :
//5
//2 9 1 2 7
//
//Output :
//  6

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {
  class MissingCoinSum {
  public:

    MissingCoinSum(vector<int> coins) : coins_{coins} {
      ranges::sort(coins_);
    }


    int64_t work() {
      int64_t result{};
      size_t size = coins_.size();
      if (coins_[0] > 1) {
        return coins_[0] - 1;
      } else if (size == 1) {
        return 2;
      }

      size_t currIdx{};
      int64_t currMaxSum = 1;
      for (size_t i = 1; i < size; i++) {
        int currCoin = coins_[i];
        if (currCoin > currMaxSum + 1) {
          return currMaxSum + 1;
        }
        currMaxSum += currCoin;
      }
      return currMaxSum + 1;
    }


  private:
    vector<int> coins_;
  };



  void check(vector<int> coins, int64_t expected) {
    MissingCoinSum missingCoinSum(coins);
    auto result = missingCoinSum.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }

}



void demo_MissingCoinSum() {
  try {
    println("demo_MissingCoinSum started ...");

    //vector<int> coins{2, 9, 1, 2, 7}; // expected = 6
    vector<int> coins{1, 2};
    MissingCoinSum missingCoinSum(coins);
    auto result = missingCoinSum.work();
    println("result = {}", result);


    check({1}, 2);
    check({2}, 1);
    check({1, 2}, 4);
    check({1, 2, 2}, 6);
    check({1, 2, 3}, 7);
    check({1, 2, 3, 6}, 13);
    check({1, 2, 3, 7}, 14);
    check({1, 2, 3, 8}, 7);
    check({1, 2, 3, 100}, 7);

    check({1, 3, 4}, 2);
    check({1, 2, 4}, 8);



    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}