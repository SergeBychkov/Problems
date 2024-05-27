//You are in a book shop which sells n different books.You know the price and number of pages of each book.
//You have decided that the total price of your purchases will be at most x.What is the maximum number of pages you can buy ? You can buy each book at most once.
//Input
//The first input line contains two integers n and x : the number of books and the maximum total price.
//The next line contains n integers h_1, h_2, \ldots, h_n: the price of each book.
//The last line contains n integers s_1, s_2, \ldots, s_n: the number of pages of each book.
//Output
//Print one integer : the maximum number of pages.
//Constraints
//
//1 \le n \le 1000
//1 \le x \le 10 ^ 5
//1 \le h_i, s_i \le 1000
//
//Example
//Input :
//4 10
//4 8 5 3
//5 12 8 1
//
//Output :
//  13
//
//  Explanation : You can buy books 1 and 3. Their price is 4 + 5 = 9 and the number of pages is 5 + 8 = 13.

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "../Utils/print_utils.h"
#include "../Utils/random_utils.h"
using namespace std;

namespace {
  auto chmax = [](auto& A, auto&& B) { return B > A ? A = B, true : false; };

  class BookShop {
  public:

    BookShop(int maxSum, vector<int> prices, vector<int> pages) : maxSum_{maxSum}, prices_{prices}, pages_{pages}, size_{(int)prices.size()} {}

    int solve(int idx, int maxSum, bool verbose = false) {
      if (idx == size_ - 1) {
        if (prices_[idx] <= maxSum) {
          return pages_[idx];
        } else {
          return -1;
        }
      }

      if (maxSum <= 0)
        return -1;

      int result1, result2;
      if (prices_[idx] <= maxSum) {
        result1 = solve(idx + 1, maxSum - prices_[idx], verbose); //with current idx
        if (result1 != -1)
          result1 = pages_[idx] + result1;
        else
          result1 = pages_[idx];
      } else {
        result1 = -1;
      }
      result2 = solve(idx + 1, maxSum, verbose);                  //without current idx 

      if (result1 == -1) {
        return result2;
      } else if (result2 == -1) {
        return result1;
      } else {
        return max(result1, result2);
      }
    }



    int workRecurs(bool verbose = false) {
      int result{};
      result = solve(0, maxSum_, verbose);
      return result;
    }



    int workArr(bool verbose = false) {
      //https://github.com/the-hyp0cr1t3/CC/blob/master/CSES/Dynamic%20Programming/Book%20Shop.cpp
      vector<int> dp(2e5 + 5);
      for (int i = 0; i < size_; i++) {
        for (int sum = maxSum_; sum >= prices_[i]; sum--) {
          chmax(dp[sum], dp[sum - prices_[i]] + pages_[i]);
          if (verbose) {
            print("i = {}, sum = {:2}, sum-prices_[i] = {}  ", i, sum, sum - prices_[i]);  Print::printVector(dp, 3, 0, 20);
          }
        }
      }
      return *max_element(dp.begin(), dp.begin() + maxSum_ + 1);
    }


    int workFullScan() {
      int result = 0;
      const int64_t power_size = pow(2, size_);
      for (int64_t i = 0; i < power_size; i++) {
        int currSum = 0;
        int currPages = 0;
        for (int j = 0; j < size_; j++) {
          if (i & (1 << j)) {
            currSum += prices_[j];
            currPages += pages_[j];
            if (currSum > maxSum_)
              break;
          }
          if (currPages > result)
            result = currPages;
        }
      }
      return result;
    }



  private:
    int maxSum_;
    vector<int> prices_;
    vector<int> pages_;
    int size_;
  };



  void check(int maxSum, vector<int> prices, vector<int> pages, int expected) {
    BookShop bookShop(maxSum, prices, pages);
    auto result1 = bookShop.workRecurs();
    auto result2 = bookShop.workArr();
    auto result3 = bookShop.workFullScan();
    if (result1 != expected || result2 != expected || result3 != expected) {
      println("maxSum = {}, ", maxSum);
      print("prices: "); Print::printVector(prices, 3);
      print("pages : "); Print::printVector(pages, 3);
      println("Error with result1 = {}, result2 = {}, result3 = {}, expected = {}", result1, result2, result3, expected);
      throw exception("Error!");
    }
  }



  void demoHelper(int maxSum, vector<int> prices, vector<int> pages) {
    BookShop bookShop(maxSum, prices, pages);
    println("maxSum = {}, ", maxSum);
    print("prices: "); Print::printVector(prices, 3);
    print("pages : "); Print::printVector(pages, 3);

    auto result1 = bookShop.workRecurs(true);
    println("max pages Recurs   = {}", result1);
    auto result2 = bookShop.workArr(true);
    println("max pages Arr      = {}", result2);
    auto result3 = bookShop.workFullScan();
    println("max pages FullScan = {}", result3);

  }



  void bench() {
    //int size = 33; //without FullScan
    int size = 26;   //with FullScan
    int maxSum = 10e5;
    auto prices = Random::getRandomIntVector(size, 1, 100);
    auto pages = Random::getRandomIntVector(size, 1, 100);
    BookShop bookShop(maxSum, prices, pages);

    auto t1 = chrono::high_resolution_clock::now();
    auto result1 = bookShop.workRecurs();
    auto t2 = chrono::high_resolution_clock::now();
    println("max pages 1 = {}", result1);
    println("duration Recurs  : {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    t1 = chrono::high_resolution_clock::now();
    auto result2 = bookShop.workRecurs();
    t2 = chrono::high_resolution_clock::now();
    println("max pages 2 = {}", result2);
    println("duration Array   : {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    t1 = chrono::high_resolution_clock::now();
    auto result3 = bookShop.workFullScan();
    t2 = chrono::high_resolution_clock::now();
    println("max pages 3 = {}", result3);
    println("duration FullScan: {} sec", (double)(t2 - t1).count() / 1'000'000'000);
  }
}



void demo_BookShop() {
  try {
    println("demo_BookShop started ...\n");

    demoHelper(10, {4, 8, 5, 3},
      {5, 12, 8, 1}); //example

    check(10, {5, 5}, {10, 20}, 30);
    check(10, {5, 6}, {10, 20}, 20);
    check(10, {6, 5}, {10, 20}, 20);

    check(10, {6, 5, 1}, {10, 20, 40}, 60);
    check(10, {6, 10, 2}, {10, 20, 40}, 50);

    bench();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}