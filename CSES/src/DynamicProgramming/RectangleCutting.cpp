//Given an a \times b rectangle, your task is to cut it into squares.On each move you can select a rectangle and cut it into two rectangles in such a way that all side lengths remain integers.What is the minimum possible number of moves ?
//Input
//The only input line has two integers a and b.
//Output
//Print one integer : the minimum number of moves.
//Constraints
//
//1 \le a, b \le 500
//
//Example
//Input :
//3 5
//
//Output :
//  3

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
using namespace std;

namespace {

  auto chmin = [](auto& A, auto&& B) { return B < A ? A = B, true : false; };

  class RectangleCutting {
  public:

    RectangleCutting(int a, int b) : a_{a}, b_{b} {
      int maxSide = max(a_, b_);
      vector<int> temp(maxSide+1);
      for (size_t i = 0; i <= maxSide; i++) {
        cache_.push_back(temp);
      }
    }


    int workWrong() { // wrong! See 5 and 6 - result must be 4!
      int result{};
      if (a_ == b_)
        return 0;

      int a = a_, b = b_;
      while (true) {
        auto [minSide, maxSide] = minmax({a, b}); // without {} returns references!
        a = minSide;
        b = maxSide - minSide;
        result++;
        if (a == b)
          break;
      }
      return result;
    }


    int solve(int a, int b) {
      if (a == b)
        return 0;
      if (a == 1)
        return b - 1;
      if (b == 1)
        return a - 1;

      int& cacheResult = cache_[a][b];
      if (cacheResult != 0) {
        return cacheResult;
      }

      int result = numeric_limits<int>::max();
      for (size_t i = 1; i <= a - 1; i++) {
        int curr = solve(i, b) + solve(a - i, b) + 1;
        if (curr < result)
          result = curr;
      }
      for (size_t i = 1; i <= b - 1; i++) {
        int curr = solve(a, i) + solve(a, b - i) + 1;
        if (curr < result)
          result = curr;
      }
      if (cacheResult == 0) {
        cacheResult = result;
      }
      return result;
    }


    int workRecurs() {
      return solve(a_, b_);
    }



    const int INF = 0x3f3f3f3f;
    //int dp_[501][501];
    int dp_[101][101];

    int solveJonathan(int a, int b) {
      //https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Dynamic%20Programming/Rectangle%20Cutting.cpp
      if (a > b) swap(a, b);
      if (dp_[a][b] != INF)    return dp_[a][b];
      if (a == b)              return dp_[a][b] = 0;
      if (a == 1 || b == 1)    return dp_[a][b] = (a == 1 ? b - 1 : a - 1);
      for (int i = 1; i < a; i++)
        dp_[a][b] = min(dp_[a][b], solveJonathan(i, b) + solveJonathan(a - i, b) + 1);
      for (int i = 1; i < b; i++)
        dp_[a][b] = min(dp_[a][b], solveJonathan(a, i) + solveJonathan(a, b - i) + 1);
      return dp_[a][b];
    }

    int workJonathan() {
      memset(dp_, 0x3f, sizeof(dp_));
      return solveJonathan(a_, b_);
    }



    int workGeeks() {
      //https://www.geeksforgeeks.org/cses-solutions-rectangle-cutting/
      // dp[][] table such that dp[i][j] stores the minimum
      // number of cuts required to cut a rectangle of size (i
      // X j) into squares
      vector<vector<int> > dp(a_ + 1, vector<int>(b_ + 1, 1e9));
      for (int i = 0; i <= a_; i++) {
        for (int j = 0; j <= b_; j++) {
          // If the rectangle is already a square, then 0
          // cuts are required
          if (i == j) {
            dp[i][j] = 0;
          } else {
            // Iterate over all the possible cuts we can
            // make horizontally
            for (int k = 1; k < j; k++) {
              dp[i][j]
                = min(dp[i][j],
                  dp[i][k] + dp[i][j - k] + 1);
            }
            // Iterate over all the possible cuts we can
            // make vertically
            for (int k = 1; k < i; k++) {
              dp[i][j]
                = min(dp[i][j],
                  dp[k][j] + dp[i - k][j] + 1);
            }
          }
        }
      }
      // Return the minimum  number of cuts required to cut a
      // rectangle of size (A X B) into squares
      return dp[a_][b_];
    }


  private:
    int a_;
    int b_;
    vector<vector<int>> cache_;
  };



  void check(int a, int b, int expected) {
    RectangleCutting rectangleCutting(a, b);
    auto result1 = rectangleCutting.workRecurs();
    auto result2 = rectangleCutting.workJonathan();
    auto result3 = rectangleCutting.workGeeks();
    if (result1 != expected || result2 != expected || result3 != expected) {
      println("Error with result1 = {}, result2 = {},  result3 = {}, expected = {}", result1, result2, result3 = {}, expected);
      throw exception("Error!");
    }
  }


  void autoCheck() {
    int aMax = 100;
    int bMax = 10;
    for (size_t a = 1; a <= aMax; a++) {
      for (size_t b = 1; b <= bMax; b++) {
        RectangleCutting rectangleCutting(a, b);
        auto result1 = rectangleCutting.workRecurs();
        auto result2 = rectangleCutting.workJonathan();
        auto result3 = rectangleCutting.workGeeks();
        if (result1 != result2 || result1 != result3 || result2 != result3) {
          println("a = {}, b = {}, result1 = {}, result2 = {}, result3 = {}", a, b, result1, result2, result3);
          throw exception("Error in autoCheck!");
        }
      }
    }
    println("autoCheck passed!");
  }
}



void demo_RectangleCutting() {
  try {
    println("demo_RectangleCutting started ...\n");
    //may stack overflow because of large dp_!
    int a = 5;
    int b = 6;
    RectangleCutting rectangleCutting(a, b);
    //auto result1 = rectangleCutting.workWrong(); //wrong! right answer = 4! 
    auto result1 = rectangleCutting.workRecurs();
    auto result2 = rectangleCutting.workJonathan();
    auto result3 = rectangleCutting.workGeeks();
    println("a = {}, b = {}", a, b);
    println("workRecurs   = {}", result1);
    println("workJonathan = {}", result2);
    println("workGeeks    = {}", result3);

    check(1, 1, 0);
    check(1, 2, 1);
    check(1, 3, 2);
    check(2, 4, 1);
    check(5, 3, 3);

    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}