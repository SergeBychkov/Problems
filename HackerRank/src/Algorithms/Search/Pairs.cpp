//https:

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

  int pairs(int k, vector<int> arr, bool verbose = false) {
    multiset<int> arrSet(arr.begin(), arr.end());
    int result = 0;
    for (auto item : arrSet) {
      result += arrSet.count(item - k);
    }
    return result;
  }



  void check(int k, vector<int> arr, int expected, bool verbose = false) {
    if (verbose) {
      //println("checking ...");
    }
    auto result = pairs(k, arr, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_Pairs() {
  try {
    println("demo_Pairs started ...\n");

    check(1, {1, 2, 3, 4}, 3, true);



    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}