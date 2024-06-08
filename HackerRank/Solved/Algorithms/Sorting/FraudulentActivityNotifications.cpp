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
  void printVec(const vector<int>& vec) {
    println("indexes:");
    for (size_t i = 0; i < vec.size(); i++) {
      print("{:8}", i);
    }
    println("\nvec:");
    for (auto item : vec) {
      print("{:8}", item);
    }
    println("");
  }


  void printSet(const multiset<int>& data) {
    print("[");
    for (const auto& element : data) {
      print("{}, ", element);
    }
    print("]");
  }


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



  int activityNotificationsWithTwoSets(vector<int> vec, int d, bool verbose = false) {
    int result = 0;
    int size = vec.size();
    if (verbose) {
      println("d = {}", d);
    }
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

    bool dIsOdd = (d % 2 == 1) ? true : false;
    multiset<int> leftSet, rightSet;
    vector<int> vecFirstD(d);
    copy(vec.begin(), vec.begin() + d, vecFirstD.begin());
    sort(vecFirstD.begin(), vecFirstD.end());
    if (verbose) {
      printVec(vec);
    }
    int middleIdx = (d % 2 == 1) ? d / 2 : d / 2 - 1;
    for (size_t i = 0; i <= middleIdx; i++) {
      leftSet.insert(vecFirstD[i]);
    }
    for (size_t i = middleIdx + 1; i < d; i++) {
      rightSet.insert(vecFirstD[i]);
    }

    int mid = *leftSet.rbegin();
    int midSec = dIsOdd ? mid : *rightSet.begin();
    if (vec[d] >= mid + midSec)
      result++;

    for (size_t i = 1; i <= size - d - 1; i++) {
      mid = *leftSet.rbegin();
      int deleted = vec[i - 1];
      int added = vec[i - 1 + d];

      if (verbose) {
        println("deleted = {}, added = {}, vec[i + d] = {}", deleted, added, vec[i + d]);
        printSet(leftSet); print("  "); printSet(rightSet);
        println("");
      }

      if (added <= mid && deleted <= mid) {
        leftSet.insert(added);
        auto it = leftSet.find(deleted);
        leftSet.erase(it);
      } else if (added > mid && deleted > mid) {
        rightSet.insert(added);
        auto it = rightSet.find(deleted);
        rightSet.erase(it);
      } else if (added <= mid && deleted > mid) {
        leftSet.insert(added);
        auto it = rightSet.find(deleted);
        rightSet.erase(it);

        auto transferred = *leftSet.rbegin();
        rightSet.insert(transferred);
        it = leftSet.end();
        --it;
        leftSet.erase(it);
      } else if (deleted <= mid && added > mid) {
        rightSet.insert(added);
        auto it = leftSet.find(deleted);
        leftSet.erase(it);

        auto transferred = *rightSet.begin();
        leftSet.insert(transferred);
        rightSet.erase(rightSet.begin());
      }

      mid = *leftSet.rbegin();
      midSec = dIsOdd ? mid : *rightSet.begin();
      if (vec[i + d] >= mid + midSec)
        result++;
    }
    return result;
  }


  void check(vector<int> vec, int d, int expected, bool verbose = false) {
    auto result = activityNotifications(vec, d, verbose);
    if (result != expected) {
      print("d = {}; vec =", d);  Print::printVector(vec);
      println("Error in activityNotifications with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }

    result = activityNotificationsWithTwoSets(vec, d, verbose);
    if (result != expected) {
      print("d = {}; vec =", d);  Print::printVector(vec);
      println("Error in activityNotificationsWithTwoSets with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void autoTest() {
  for (int size = 4; size <= 10; size++) {
    vector<int> vec = Random::getRandomIntVector(size, 1, 10);
    for (size_t d = 2; d < size - 1; d++) {
      //println("size = {}, d = {}", size, d);
      //Print::printVector(vec, 8, 0, vec.size());
      auto result1 = activityNotifications(vec, d);
      auto result2 = activityNotificationsWithTwoSets(vec, d);
      if (result1 != -result2) {
        Print::printVector(vec, 8, 0, vec.size());
        throw exception("Error in autoTest!");
      }
    }
  }
  println("\nautoTest passed!");
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
    
    autoTest();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}