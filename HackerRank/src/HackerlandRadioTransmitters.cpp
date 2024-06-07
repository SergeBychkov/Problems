//https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem?isFullScreen=true

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

  int hackerlandRadioTransmitters(vector<int> vec, int k, bool verbose = false) {
    set<int> houses(vec.begin(), vec.end());
    vec.clear();
    vec.insert(vec.end(), houses.begin(), houses.end());
    int size = vec.size();
    vector<int> transmitters;

    if (verbose) {
      Print::printVector(vec);
    }

    int result = 0;
    int uncovered = 0;
    int transmitter = -1;
    int i = -1;
    while (true) {
      //searching transmitter
      if (uncovered == size - 1)
        return result + 1;
      i = uncovered + 1;
      while (true) {
        if (vec[i] - vec[uncovered] < k) {
          i++;
          if (i == size - 1) {
            return (vec[i] - vec[uncovered] < k) ? result + 2 : result + 1;
          };
          continue;
        }
        transmitter = i;  //found
        result++;
        break;
      }

      //searching uncovered
      if (transmitter == size - 1)
        return result;
      i = transmitter + 1;
      while (true) {
        if (vec[i] - vec[transmitter] < k) {
          i++;
          if (i == size - 1) {
            return (vec[i] - vec[transmitter] < k) ? result : result + 1;
          }
          continue;
        }
        uncovered = i - 1;    //found
        break;
      }

      if (verbose) {
        println("i = {}, transmitter = {}, uncovered = {}", i, transmitter, uncovered);
      }
    }

    return result;
  }



  void check(vector<int> vec, int k, int expected, bool verbose = false) {
    auto result = hackerlandRadioTransmitters(vec, k, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main_() {
  try {
    println("HackerlandRadioTransmitters started ...\n");

    //check({0, 1, 2, 3, 4}, 1, 2, true);
    check({0, 10, 20, 30, 40}, 1, 5, true);



    //check({9, 5, 4, 2, 6, 15, 12}, 2, 4);


    //check({1}, 1, 1);
    //check({1, 2}, 1, 1);
    //check({1, 2, 3}, 1, 1);
    //check({1, 2, 3, 4}, 1, 2);

    //check({1, 2, 3, 4, 5}, 1, 2);
    //check({2, 2, 2, 2, 1, 1, 1, 1}, 2, 1);
    //check({9, 5, 4, 2, 6, 15, 12}, 2, 4);



    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}