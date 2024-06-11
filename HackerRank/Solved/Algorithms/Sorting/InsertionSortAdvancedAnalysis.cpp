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

  int64_t merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int64_t inversions{0};
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
      } else {
        inversions += mid + 1 - i;
        temp[k++] = arr[j++];
      }
    }

    while (i <= mid) {
      temp[k++] = arr[i++];
    }

    while (j <= right) {
      temp[k++] = arr[j++];
    }

    for (int i = left; i <= right; i++) {
      arr[i] = temp[i];
    }
    return inversions;
  }



  int64_t mergeSort(vector<int>& arr, bool verbose = false) {
    int n = arr.size();
    vector<int> temp(n);
    int64_t inversions{0};
    for (int size = 1; size < n; size *= 2) {
      for (int left_start = 0; left_start < n - 1; left_start += 2 * size) {
        int mid = min(left_start + size - 1, n - 1);
        int right_end = min(left_start + 2 * size - 1, n - 1);
        if (verbose) {
          println("size = {}, left_start = {}, mid = {}, right_end = {}", size, left_start, mid, right_end);
        }
        inversions += merge(arr, temp, left_start, mid, right_end);
      }
    }
    return inversions;
  }



  int64_t insertionSort(vector<int> vec, bool verbose) {
    return mergeSort(vec, verbose);
  }



  int inversionsByFullScan(const vector<int> vec) {
    int result = 0;
    int size = vec.size();
    for (size_t i = 0; i < size - 1; i++) {
      for (size_t j = i + 1; j < size; j++) {
        if (vec[i] > vec[j])
          result++;
      }
    }
    return result;
  }



  void check(vector<int> arr, int expected, bool verbose = false) {
    auto result = insertionSort(arr, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }



  void testMergeSort(const vector<int>& arr, bool verbose = false) {
    auto vec = arr;
    //Print::printVector(vec, 8, 0, vec.size(), true);
    int inv = mergeSort(vec, verbose);
    //Print::printVector(vec);
    //println("inversions = {}", inv);
    
    vec = arr;
    int invByFullScan = inversionsByFullScan(vec);
    if (inv != invByFullScan) {
      println("Error in testMergeSort with result = {}, expected = {}", inv, invByFullScan);
      throw exception("Error!");
    }
  }



  void autoTest() {
    for (int size = 2; size <= 100; size++) {
      vector<int> vec = Random::getRandomIntVector(size, 1, 10);
      for (size_t d = 2; d < size - 1; d++) {
        testMergeSort(vec);
      }
    }
    println("\nautoTest passed!");
  }
}



void main() {
  try {
    println("InsertionSortAdvancedAnalysis started ...\n");

    vector<int> vec{4, 3, 2, 1};
    testMergeSort(vec, false);

    check({4, 3, 2, 1}, 6);
    check({1, 1, 1, 2, 2}, 0);
    check({2, 1, 3, 1, 2}, 4);

    autoTest();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}