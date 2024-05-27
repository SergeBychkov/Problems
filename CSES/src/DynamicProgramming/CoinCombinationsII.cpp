//Consider a money system consisting of n coins.Each coin has a positive integer value.Your task is to calculate the number of distinct ordered ways you can produce a money sum x using the available coins.
//For example, if the coins are \{2, 3, 5\} and the desired sum is 9, there are 3 ways:
//
//2 + 2 + 5
//3 + 3 + 3
//2 + 2 + 2 + 3
//
//Input
//The first input line has two integers n and x: the number of coins and the desired sum of money.
//The second line has n distinct integers c_1, c_2, \dots, c_n: the value of each coin.
//Output
//Print one integer : the number of ways modulo 10 ^ 9 + 7.
//Constraints
//
//1 \le n \le 100
//1 \le x \le 10 ^ 6
//1 \le c_i \le 10 ^ 6
//
//Example
//Input :
//3 9
//2 3 5
//
//Output :
//  3

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <set>
using namespace std;

namespace {

  struct SavedResult {
    bool ready{false};
    int result{};
  };



  class CoinCombinationsII {
  public:

    CoinCombinationsII(int sum, vector<int> coins) : sum_{sum}, coins_{coins} { // sum+1 ! {}
      ranges::sort(coins_);
      auto last = std::unique(coins_.begin(), coins_.end()); // removes repetitions
      coins_.erase(last, coins_.end());
    }



    int solve(int sum, int currentCoin) {
      if (sum < 0) return -1;
      if (sum == 0) return 1;
      int result = -1;
      bool wasFound{false};

      for (auto coin : coins_) {
        if (coin < currentCoin)
          continue;

          int arg = sum - coin;
          if (arg < 0)
            break;

          int subResult = solve(arg, coin);
          if (subResult == -1)
            continue;
          if (!wasFound) {
            result = subResult;
            wasFound = true;
          } else {
            result = result + subResult;
          }
      }
      return result;
    }



    int work() {
      if (coins_.size() == 1) {
        return  (sum_ % coins_[0] == 0) ? 1 : 0;
      }
      return solve(sum_, coins_[0]);
    }



    void printInput() {
      print("sum = {}, coins = (", sum_);
      for (size_t i = 0; i < coins_.size(); i++) {
        print("{}, ", coins_[i]);
      }
      println(")");
    }


  private:
    int sum_;
    vector<int> coins_;
  };





  void check(int sum, vector<int> coins, int expected) {
    CoinCombinationsII solver(sum, coins);
    int result = solver.work();
    if (result != expected) {
      println("Error with sum = {}, result = {}, expected = {}", sum, result, expected);
      solver.printInput();
      throw exception("Error!");
    }
  }
}



void demo_CoinCombinationsII() {
  try {
    int result{};
    //int sum = 9;
    //vector<int> coins{{2, 3, 5}};
    int sum = 4;
    vector<int> coins{{1, 2}};

    CoinCombinationsII solver(sum, coins);
    solver.printInput();
    result = solver.work();
    println("result = {}", result);

    //return;

    check(2, {2}, 1);
    check(3, {2}, 0);
    check(2, {3}, 0);

    check(2, {1, 1}, 1);
    check(3, {1, 1}, 1);
    check(3, {2, 1}, 2);

    check(4, {2}, 1);

    check(3, {1, 2}, 2);
    check(4, {1, 2}, 3);

    check(4, {1, 2, 3}, 4);

    //check(1, {1}, 1);
    //check(1, {2}, -1);
    //check(3, {1, 2}, 3);
    //check(3, {1, 2, 3}, 4);
    check(9, {2, 3, 5}, 3); //bad

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}