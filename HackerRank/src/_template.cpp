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

  int solve(/*  */ bool verbose = false) {



    return 0;
  }



  void check(/*  */ int expected, bool verbose = false) {
    auto result = solve(verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void _main() {
  try {
    println("demo_QqqVova started ...\n");

    check(/*  */ 0, true);



    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}