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

  struct Item {
    int value{};
    int idxOther{};
  };

  void printVec(const vector<Item>& vec) {
    for (const auto& item : vec) {
      print("{:8}", item.value);
    }
    println("");
    for (const auto& item : vec) {
      print("{:8}", item.idxOther);
    }
    println("");
  }


  void printVectors(const vector<int>& origVec, const vector<Item>& sortedVec, const vector<Item>& outVec) {
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
    println("out:");
    printVec(outVec);
    println("");
  }


  int lilysHomeworkImpl(vector<int> origVec, bool asc, bool verbose = false) {
    int result = 0;
    int size = origVec.size();
    vector<Item> sortedVec(size);
    transform(origVec.begin(), origVec.end(), sortedVec.begin(), [n = 0](int value) mutable {
      return Item{value, n++};
      });
    vector<Item> outVec(size);
    transform(origVec.begin(), origVec.end(), outVec.begin(), [n = 0](int value) mutable {
      return Item{value, -1};
      });

    if (asc)
      sort(sortedVec.begin(), sortedVec.end(), [](Item a, Item b) {return a.value < b.value; });
    else
      sort(sortedVec.begin(), sortedVec.end(), [](Item a, Item b) {return b.value < a.value; });

    for (size_t i = 0; i < size; i++) {
      int idx = sortedVec[i].idxOther;
      outVec[idx].idxOther = i;
    }

    if (verbose)
      printVectors(origVec, sortedVec, outVec);

    for (size_t i = 0; i < size; i++) {
      if (sortedVec[i].value != outVec[i].value)
        result++;

      int firstIdx = i;
      int secIdx = sortedVec[i].idxOther;
      Item& first = outVec[firstIdx];
      Item& sec = outVec[secIdx];

      int temp = first.value;
      first.value = sec.value;
      sec.value = temp;

      sec.idxOther = first.idxOther;
      sortedVec[first.idxOther].idxOther = secIdx;
    }
    if (verbose) {
      println("\nin the end:");
      printVectors(origVec, sortedVec, outVec);
      println("----------------------------------------------------------------\n");
    }
    return result;
  }


  int lilysHomework(vector<int> origVec, bool verbose = false) {
    int res1 = lilysHomeworkImpl(origVec, true, verbose);
    int res2 = lilysHomeworkImpl(origVec, false, verbose);
    return min(res1, res2);
  }


  void check(vector<int> arr, int expected, bool verbose = false) {
    auto result = lilysHomework(arr, verbose);
    if (result != expected) {
      Print::printVector(arr);
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main() {
  try {
    println("LilysHomework started ...\n");

    check({2, 3, 1, 3, 2, 3}, 3);
    check({2, 3, 1, 3, 2, 3, 1}, 3);

    check({7, 15, 12, 3}, 2);
    check({2, 5, 3, 1}, 2);

    //from site tests
    check({3, 4, 2, 5, 1}, 2);
    check({2, 5, 3, 1}, 2);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}