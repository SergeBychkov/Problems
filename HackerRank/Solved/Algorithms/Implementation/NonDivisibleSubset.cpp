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

  int nonDivisibleSubset(int k, vector<int> arr, bool verbose = false) {
    int result = 0;
    vector<int> vec(k);
    for (size_t i = 0; i < arr.size(); i++) {
      vec[arr[i] % k]++;
      //println("{} - {}", arr[i] % k, arr[i]);
    }
    if (verbose) {
      Print::printVector(vec, 8, 0, k, true);
    }

    int mid = k / 2;
    bool kIsEven = k % 2 == 0;
    int finish = (kIsEven) ? mid - 1 : mid;

    if (vec[0] > 0) // add one devided on k
      result++;
    if (kIsEven) //add one middle!!!
      result++;

    for (size_t i = 1; i <= finish; i++) {
      result += max(vec[i], vec[k - i]);
    }
    return result;
  }




  void check(int k, vector<int> s, int expected, bool verbose = false) {
    auto result = nonDivisibleSubset(k, s, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main() {
  try {
    println("NonDivisibleSubset started ...\n");

    check(4, {19, 10, 12, 24, 25, 22}, 3, true);
    check(4, {1, 7, 2, 4}, 3, true);



    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}