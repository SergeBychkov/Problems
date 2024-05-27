//Consider a money system consisting of n coins.Each coin has a positive integer value.Your task is to calculate the number of distinct ways you can produce a money sum x using the available coins.
//For example, if the coins are \{2, 3, 5\} and the desired sum is 9, there are 8 ways:
//
//2 + 2 + 5
//2 + 5 + 2
//5 + 2 + 2
//3 + 3 + 3
//2 + 2 + 2 + 3
//2 + 2 + 3 + 2
//2 + 3 + 2 + 2
//3 + 2 + 2 + 2
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
//Out

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {

  struct SavedResult {
    bool ready{false};
    int result{};
  };



  class CoinCombinationsI {
  public:

    CoinCombinationsI(int sum, vector<int> coins) : sum_{sum}, coins_{coins}, results_{vector<int>(sum + 1)} { // sum+1 ! {}
      ranges::sort(coins_);
    }


    int work() {
      results_[0] = 0;
      for (int x = 1; x <= sum_; x++) {
        int result = 0;
        for (auto coin : coins_) {
          int arg = x - coin;
          if (arg < 0) { // coins_ are sorted
            break;
          } else if (arg == 0) {
            result++;
            continue;
          }
          int subResult = results_[arg];
          if (subResult != -1)
            result += subResult;
        }
        results_[x] = (result != 0) ? result : -1;
      }
      return results_[sum_];
    }



    void printResults() {
      print("sum = {}, coins = (", sum_);
      for (size_t i = 0; i < coins_.size(); i++) {
        print("{}, ", coins_[i]);
      }
      println("), result = {}", results_[sum_]);
      for (size_t i = 0; i < results_.size(); i++) {
        print("{}, ", results_[i]);
      }
      println("");
    }


  private:
    int sum_;
    vector<int> coins_;
    vector<int> results_;
  };





  void check(int sum, vector<int> coins, int result) {
    CoinCombinationsI solver(sum, coins);
    if (solver.work() != result) {
      println("Error with sum = {}, result = {}", sum, result);
      throw exception("Error!");
    }
  }
}



void demo_CoinCombinationsI() {
  try {
    int result{};
    //int sum = 5;
    //vector<int> coins{{1, 3, 4}};
    int sum = 10;
    vector<int> coins{{5, 2}};
    CoinCombinationsI solver(sum, coins);
    result = solver.work();
    solver.printResults();

    check(0, {1}, 0);
    check(1, {1}, 1);
    check(1, {2}, -1);
    check(3, {1, 2}, 3);
    check(3, {1, 2, 3}, 4);
    check(5, {1, 3, 4}, 6);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}