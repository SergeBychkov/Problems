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



  class MinimizingCoins {
  public:

    MinimizingCoins(int sum, vector<int> coins) : sum_{sum}, coins_{coins}, savedResults_{vector<SavedResult>(sum)} {}


    int solveLaaksonen(int n) {
      //bad, if cannot been solved, returns anything
      constexpr int INF = std::numeric_limits<int>::max() / 2; // if simply max() then overflow!!!
      if (n < 0) return INF;
      if (n == 0) return 0;
      int best = INF;

      for (auto coin : coins_) {
        best = min(best, solveLaaksonen(n - coin) + 1);
      }
      return best;
    }



    int solve(int n) { // very slow!
      if (n < 0) return -1; //cannot solve 
      if (n == 0) return 0;

      int result{0};
      bool wasFound{false};
      for (auto coin : coins_) {
        int subResult = solve(n - coin);
        if (subResult == -1)
          continue;

        if (!wasFound) {
          result = subResult + 1;
          wasFound = true;
        } else {
          result = min(result, subResult + 1);
        }
      }
      return (wasFound) ? result : -1;
    }



    int solveWithCache(int n) { // very quick!
      if (n < 0) return -1; //cannot solve 
      if (n == 0) return 0;

      int result{0}, subResult;
      bool wasFound{false};
      for (auto coin : coins_) {
        int arg = n - coin;
        if (arg >= 0) {
          if (savedResults_[arg].ready) {
            subResult = savedResults_[arg].result;
          } else {
            subResult = solveWithCache(arg);
            savedResults_[arg].ready = true;
            savedResults_[arg].result = subResult;
          }
        } else {
          subResult = solveWithCache(arg);
        }
        if (subResult == -1)
          continue;

        if (!wasFound) {
          result = subResult + 1;
          wasFound = true;
        } else {
          result = min(result, subResult + 1);
        }
      }
      return (wasFound) ? result : -1;
    }



    int workLaaksonen() {
      return solveLaaksonen(sum_);
    }

    int work() {
      return solve(sum_);
    }

    int workWithCache() {
      auto result = solveWithCache(sum_);
      return result;
    }


  private:
    int sum_;
    vector<int> coins_;
    vector<SavedResult> savedResults_;
  };



  class MinimizingCoinsIterat {
  public:

    MinimizingCoinsIterat(int sum, vector<int> coins) : sum_{sum}, coins_{coins}, results_{vector<int>(sum + 1)}, firstCoinInOptimal_{vector<int>(sum + 1)} { // sum+1 !
      ranges::sort(coins_);
    }


    int work() {
      results_[0] = 0;
      for (int x = 1; x <= sum_; x++) {
        int result = -1;
        bool wasFound{false};
        for (auto coin : coins_) {
          if (x - coin < 0) // coins_ are sorted
            break;
          int subResult = results_[x - coin];
          if (subResult == -1)
            continue;
          if (!wasFound) {
            result = subResult + 1;
            wasFound = true;
          } else {
            result = min(result, subResult + 1);
          }
          firstCoinInOptimal_[x] = coin;
        }
        results_[x] = result;
      }
      return results_[sum_];
    }



    void printResults() {
      print("sum = {}, coins = (", sum_);
      for (size_t i = 0; i < coins_.size(); i++) {
        print("{}, ", coins_[i]);
      }
      println("), resultIter = {}", results_[sum_]);
      for (size_t i = 0; i < results_.size(); i++) {
        print("{}, ", results_[i]);
      }

      println("\ncoins: ");
      int n = sum_;
      while (n > 0) {
        print("{}, ", firstCoinInOptimal_[n]);
        n -= firstCoinInOptimal_[n];
      }
      println("");
    }


  private:
    int sum_;
    vector<int> coins_;
    vector<int> results_;
    vector<int> firstCoinInOptimal_;
  };


  void check(int sum, vector<int> coins, int result) {
    MinimizingCoins solver(sum, coins);
    if (solver.work() != result) {
      println("Error with sum = {}, result = {}", sum, result);
      throw exception("Error!");
    }

    MinimizingCoinsIterat solverIter(sum, coins);
    if (solverIter.work() != result) {
      println("Error with sum = {}, result = {}", sum, result);
      throw exception("Error!");
    }
  }

}



void demo_MinimizingCoins() {
  try {
    println("Started ...");
    int result{};
    int sum = 20;
    vector<int> coins{{2, 6, 4}};

    MinimizingCoins solver(sum, coins);
    result = solver.work();
    println("result            = {}", result);
    result = solver.workWithCache();
    println("result with Cache = {}", result);

    MinimizingCoinsIterat solverIter(sum, coins);
    solverIter.work();
    solverIter.printResults();


    check(0, {1}, 0);
    check(10, {9}, -1);
    check(10, {10}, 1);
    check(10, {5}, 2);
    check(10, {5, 1}, 2);

    check(4, {1, 2}, 2);
    check(10, {1, 3, 4}, 3);
    check(10, {1, 3, 5}, 2);
    check(10, {1, 3, 6}, 3);


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}