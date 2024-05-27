//There is a street of length x whose positions are numbered 0, 1, \ldots, x.Initially there are no traffic lights, but n sets of traffic lights are added to the street one after another.
//Your task is to calculate the length of the longest passage without traffic lights after each addition.
//Input
//The first input line contains two integers x and n: the length of the street and the number of sets of traffic lights.
//Then, the next line contains n integers p_1, p_2, \ldots, p_n: the position of each set of traffic lights.Each position is distinct.
//Output
//Print the length of the longest passage without traffic lights after each addition.
//Constraints
//
//1 \le x \le 10 ^ 9
//1 \le n \le 2 \cdot 10 ^ 5
//0 < p_i < x
//
//  Example
//  Input :
//8 3
//3 6 2
//
//Output :
//  5 3 3

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  class TrafficLights {
  public:

    TrafficLights(int x, vector<int>lights) :x_{x}, lightsVec_{lights} {}


    int work(bool verbose = false) {
      int longest{x_};
      set<int> lights{0, x_};
      multiset<int> lengths{x_};
      for (auto item : lightsVec_) {
        auto it = lights.lower_bound(item);
        auto predIter = it; predIter--;
        auto firstPart = item - *predIter;
        auto secPart = *it - item;

        auto deleteIt = ranges::find(lengths, (*it - *predIter));
        lengths.erase(deleteIt);
        lengths.insert(firstPart);
        lengths.insert(secPart);

        lights.insert(item);
        if (verbose) {
          Print::printIterator(lengths.begin(), lengths.end(), 3);
          println("longest = {}", *lengths.rbegin());
          println("------------------------------------------\n");
        }
      }
      return *lengths.rbegin();
    }


  private:
    int x_;
    vector<int> lightsVec_;
  };



  void check(int x, vector<int> lights, int expected) {
    TrafficLights trafficLights(x, lights);
    auto result = trafficLights.work(true);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_TrafficLights() {
  try {
    println("demo_TrafficLights started ...");

    int x = 8;
    vector<int> lights{3, 6, 2};
    TrafficLights trafficLights(x, lights);
    auto result = trafficLights.work();
    print("x = {}, lights = ", x); Print::printVector(lights, 3);
    println("result = {}", result);

    check(8, {3, 6, 2}, 3);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}