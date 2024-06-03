//https://www.hackerrank.com/challenges/minimum-loss/problem?isFullScreen=true

#include <print>
#include <vector>
#include <deque>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {

  struct House {
    long price{};
    int index{};
  };


  int minimumLoss(vector<long> price, bool verbose = false) {
    vector<House> houses;
    for (int i = 0; i < (long)price.size(); i++) {
      houses.push_back({price[i], i});
    }
    sort(houses.begin(), houses.end(), [](const House& a, const House& b) {
      return b.price < a.price; // descending
    });

    long result = INT_MAX;
    for (size_t i = 1; i < houses.size(); i++) {
      if(houses[i-1].index < houses[i].index) {
        result = min(result, houses[i-1].price - houses[i].price);
      }
    }

    return (int)result;
  }



  void check(vector<long> price, int expected, bool verbose = false) {
    if (verbose) {
      Print::printVector(price);
    }
    auto result = minimumLoss(price, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_MinimumLoss() {
  try {
    println("demo_MinimumLoss started ...\n");

    check({20, 15, 8, 2, 12}, 3, true);
    check({20, 7, 8, 2, 5}, 2, true);
    


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}