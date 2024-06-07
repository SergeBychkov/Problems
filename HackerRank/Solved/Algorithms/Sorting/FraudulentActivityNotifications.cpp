//https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem?isFullScreen=true

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

  int activityNotifications(vector<int> vec, int d, bool verbose = false) {
    int result = 0;
    int size = vec.size();
    if (size == 1 || d == size) {
      return 0;
    }
    if (d == 1) {
      for (size_t i = 1; i < size; i++) {
        result += ((vec[i] >= 2 * vec[i - 1]) ? 1 : 0);
      }
      return result;
    }
    if (d == 2) {
      for (size_t i = 2; i < size; i++) {
        result += ((vec[i] >= vec[i - 1] + vec[i - 2]) ? 1 : 0);
      }
      return result;
    }

    multiset<int> values(vec.begin(), vec.begin() + d);
    bool dIsOdd = (d % 2 == 1) ? true : false;
    int middleIdx = dIsOdd ? d / 2 : d / 2 - 1;
    auto itMid = values.begin();
    for (int i = 0; i < middleIdx; i++) {
      itMid++;
    }

    auto itSec = dIsOdd ? itMid : next(itMid);
    if (vec[d] >= *itMid + *itSec)
      result++;

    for (size_t i = 1; i <= size - d - 1; i++) {
      int valueMid = *itMid;
      int deleted = vec[i - 1];
      int added = vec[i - 1 + d];

      auto itToDelete = values.lower_bound(deleted);
      values.erase(itToDelete);
      auto itAdded = values.insert(added);

      if (deleted == valueMid) { //repeat search
        itMid = values.begin();
        for (int i = 0; i < middleIdx; i++) {
          itMid++;
        }
      } else {
        if (added < valueMid && deleted > valueMid) {
          itMid--;
        } if (added >= valueMid && deleted < valueMid) {
          itMid++;
        }
      }

      itSec = dIsOdd ? itMid : next(itMid);
      if (vec[i + d] >= *itMid + *itSec)
        result++;
    }
    return result;
  }



  void check(vector<int> vec, int d, int expected, bool verbose = false) {
    if (verbose) {
      println("checking ...");
    }
    auto result = activityNotifications(vec, d, verbose);
    if (result != expected) {
      print("d = {}; vec =", d);  Print::printVector(vec);
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main() {
  try {
    println("FraudulentActivityNotifications started ...\n");

    check({1, 1}, 1, 0);
    check({1, 2}, 1, 1);
    check({1, 2}, 2, 0);
    check({1, 2, 1}, 2, 0);
    check({1, 2, 3}, 2, 1);
    check({1, 2, 4}, 2, 1);

    check({10, 20, 30, 40, 50}, 3, 1);
    check({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5, 2);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}