//https://www.hackerrank.com/challenges/insertion-sort/problem?isFullScreen=true

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

  struct Item {
    int value{};
    int idx{};
  };


  void printVec(const vector<Item>& vec) {
    for (const auto& item : vec) {
      print("{:8}", item.value);
    }
    println("");
    for (const auto& item : vec) {
      print("{:8}", item.idx);
    }
    println("");
  }


  void printVectors(const vector<int>& origVec, const vector<Item>& sortedVec) {
    println("indexes:");
    for (size_t i = 0; i < origVec.size(); i++) {
      print("{:8}", i);
    }
    println("");
    println("original:");
    Print::printVector(origVec);
    println("sorted:");
    printVec(sortedVec);
    println("");
  }



  int insertionSort(vector<int> origVec, bool verbose) {
    int result = 0;
    int size = origVec.size();
    vector<Item> sortedVec(size);
    transform(origVec.begin(), origVec.end(), sortedVec.begin(), [n = 0](int value) mutable {
      return Item{value, n++};
      });
    stable_sort(sortedVec.begin(), sortedVec.end(), [](Item a, Item b) {return a.value < b.value; });
    if (verbose) {
      printVectors(origVec, sortedVec);

    }

    for (size_t i = 1; i < size; i++) { //skip first!
      int curr = origVec[i];
      //int curr = i;
      auto end = sortedVec.begin() + i;
      auto it = upper_bound(sortedVec.begin(), end, curr, [](int value, Item a) {return value < a.value; });
      if (it != end) {
        int insertIdx = distance(sortedVec.begin(), it);
        println("curr = {}, itsertIdx = {}", curr, insertIdx);
      } else {
        println("curr = {} not found", curr);
      }
    }


    return result;
  }



  void check(vector<int> arr, int expected, bool verbose = false) {
    if (verbose) {
      println("checking ...");
    }
    auto result = insertionSort(arr, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main___() {
  try {
    println("InsertionSortAdvancedAnalysis started ...\n");

    check({4, 3, 2, 1}, 6, true);



    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}