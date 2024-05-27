//You have n coins with certain values.Your task is to find all money sums you can create using these coins.
//Input
//The first input line has an integer n : the number of coins.
//The next line has n integers x_1, x_2, \dots, x_n: the values of the coins.
//Output
//First print an integer k : the number of distinct money sums.After this, print all possible sums in increasing order.
//Constraints
//
//1 \le n \le 100
//1 \le x_i \le 1000
//
//Example
//Input :
//4
//4 2 5 2
//
//Output :
//  9
//  2 4 5 6 7 8 9 11 13

#include <print>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  class MoneySums {
  public:

    MoneySums(vector<int> coins) : coins_{coins} {}

    //Recursion
    int setSum(int sum, vector<bool>& sums) {
      if (sums[sum] == false) {
        sums[sum] = true;
        return 1;
      } else {
        return 0;
      }
    }

    int solveRecurs(unordered_multiset<int> coinsSet, vector<bool>& sums) { //instead of unordered_multiset better use vector
      int result{};
      if (coinsSet.size() == 1)
        return setSum(*coinsSet.begin(), sums);

      for (auto it = coinsSet.begin(); it != coinsSet.end(); it++) {
        unordered_multiset<int> tempSet;
        for (auto itSec = coinsSet.begin(); itSec != coinsSet.end(); itSec++) {
          if (itSec != it)
            tempSet.insert(*itSec);
        }
        //Print::printSet(tempSet, 3);
        result += setSum(*it, sums);
        result += setSum(accumulate(coinsSet.begin(), coinsSet.end(), 0), sums);
        result += solveRecurs(tempSet, sums);
      }
      return result;
    }

    int workRecurs() {
      int maxSum = accumulate(coins_.begin(), coins_.end(), 0);
      vector<bool> sums(maxSum + 1);
      unordered_multiset coins(coins_.begin(), coins_.end());
      return solveRecurs(coins, sums);

    }



    int work(bool verbose = false) {
      const int maxSum = accumulate(coins_.begin(), coins_.end(), 0) + 1;
      //set<int> sums;
      unordered_set<int> sums;
      sums.insert(0);
      for (int i = 0; i < coins_.size(); i++) {
        for (int sum = maxSum - coins_[i]; sum >= 0; sum--) {
          if (sums.contains(sum))
            sums.insert(sum + coins_[i]);
        }
      }
      return sums.size() - 1;
    }



    int workJonathan(bool verbose = false) { //the fastest!
      //https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Dynamic%20Programming/Money%20Sums.cpp
      int result{};
      int tmpSize = accumulate(coins_.begin(), coins_.end(), 0);
      vector<bool> sums(tmpSize + 1);
      const int maxSum = sums.size();

      sums[0] = true;
      for (int i = 0; i < coins_.size(); i++) {
        for (int sum = maxSum - coins_[i]; sum >= 0; sum--) {
          if (sums[sum])
            sums[sum + coins_[i]] = true;
        }
      }

      for (int i = 1; i < maxSum; i++) {
        if (sums[i]) {
          result++;
        }
      }
      if (verbose) {
        printResult(sums);
      }
      return result;
    }



  private:
    vector<int> coins_;


    void printResult(const vector<bool>& sums) {
      for (size_t i = 1; i < sums.size(); i++) {
        if (sums[i])
          print("{}, ", i);
      }
      println("");
    }
  };



  void check(vector<int> coins, int expected) {
    MoneySums moneySums(coins);
    auto result = moneySums.workRecurs();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }



  void autoCheck() {
    int size = 8;
    int nTests = 10;
    for (size_t i = 0; i < nTests; i++) {
      auto coins = Random::getRandomIntVector(size, 1, 10, true);
      MoneySums moneySums(coins);
      int result1 = moneySums.workRecurs();
      int result2 = moneySums.work();
      int result3 = moneySums.workJonathan();
      if (result1 != result2 && result2 != result3) {
        println("result1 = {}, result2 = {}, result3 = {}", result1, result2, result3);
        throw exception("Error in autoCheck!");
      }
    }
    println("\nautoCheck passed!");
  }


  void bench() {
    println("\nBenchmarking:");
    int size = 100; 
    auto coins = Random::getRandomIntVector(size, 990, 1000);
    //auto coins = Random::getRandomIntVector(size, 1000, 1000);
    MoneySums moneySums(coins);
    int maxSum = accumulate(coins.begin(), coins.end(), 0) + 1;
    println("maxSum = {}", maxSum);

    auto t1 = chrono::high_resolution_clock::now();
    auto result = moneySums.work();
    auto t2 = chrono::high_resolution_clock::now();
    println("result = {}", result);
    println("duration work        : {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    //the fastest!
    t1 = chrono::high_resolution_clock::now();
    result = moneySums.workJonathan();
    t2 = chrono::high_resolution_clock::now();
    println("result = {}", result);
    println("duration workJonathan: {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    //very slow!
    //t1 = chrono::high_resolution_clock::now();
    //result = moneySums.workRecurs();
    //t2 = chrono::high_resolution_clock::now();
    //println("result = {}", result);
    //println("duration workRecurs  : {} sec", (double)(t2 - t1).count() / 1'000'000'000);
  }
}



void demo_MoneySums() {
  try {
    println("demo_MoneySums started ...\n");

    //MoneySums moneySums({1, 2, 3});
    MoneySums moneySums({4, 2, 5, 2});
    auto result = moneySums.workRecurs();
    println("result workRecurs   = {}", result);
    result = moneySums.work(true);
    println("result work         = {}", result);
    result = moneySums.workJonathan(true);
    println("result workJonathan = {}", result);

    //autoCheck();
    bench();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}