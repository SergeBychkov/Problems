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

  void printCountries(const vector<vector<int>>& countries) {
    println("countries:");
    for (auto item : countries) {
      Print::printVector(item);
    }
    println("");
  }


  int64_t journeyToMoon(int n, vector<vector<int>> astronauts, bool verbose = false) {
    unordered_set<int> visited;
    vector<vector<int>> neighbors(n);
    vector<vector<int>> countries;

    for (auto& astro : astronauts) {
      neighbors[astro[0]].push_back(astro[1]);
      neighbors[astro[1]].push_back(astro[0]);
    }

    int currentCountry = 0;
    for (size_t i = 0; i < n; i++) {
      if (visited.find(i) == visited.end()) { //new austro
        visited.insert(i);
        countries.push_back({});
        countries[currentCountry].push_back(i);
      } else {
        continue;
      }

      deque<int> stack;
      stack.push_front(i);
      while (!stack.empty()) {
        int curr = stack.back();
        stack.pop_back();
        if (verbose) {
          println("curr = {}", curr);
          print("    neighb : ");
        }
        for (size_t j = 0; j < neighbors[curr].size(); j++) {
          int neighb = neighbors[curr][j];
          if (visited.find(neighb) == visited.end()) { //new austro
            countries[currentCountry].push_back(neighb);
            visited.insert(neighb);
            stack.push_front(neighb);
          }
          //print("{}, ", neighb);
        }
        if (verbose) {
          println("");
          print("    visited: "); Print::printSet(visited);
          printCountries(countries);
        }
      }
      currentCountry++;
    }
    //printCountries(countries);

    vector<int> countriesWithout1;
    int64_t countCountriesWith1 = 0;
    for (size_t i = 0; i < countries.size(); i++) {
      int sz = countries[i].size();
      if (sz > 1)
        countriesWithout1.push_back(sz);
      else
        countCountriesWith1++;
    }

    int64_t result = 0;
    int64_t result1 = countCountriesWith1 * (countCountriesWith1 - 1) / 2;
    int64_t result2 = 0;
    int sizeWithout1 = countriesWithout1.size();
    for (size_t i = 0; i < sizeWithout1 - 1; i++) {
      for (size_t j = i + 1; j < sizeWithout1; j++) {
        result2 += (int64_t)countriesWithout1[i] * (int64_t)countriesWithout1[j];
      }
    }

    if (countCountriesWith1 > 1) {
      result =  result1 + result2 + countCountriesWith1 * (n - countCountriesWith1);
    } else if (countCountriesWith1 == 1) {
      result = result2 + (n - 1);
    } else {
      result = result2;
    }
    return result;
  }



  void check(int n, vector<vector<int>> astronauts, int64_t expected, bool verbose = false) {
    auto result = journeyToMoon(n, astronauts, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main() {
  try {
    println("JourneyToTheMoon started ...\n");

    check(4, {{1, 2}, {2, 3}}, 3, true);
    check(5, {{0, 1}, {2, 3}, {0, 4}}, 6);

    check(100000, {{1, 2}, {3, 4}}, 4999949998); //from site
          
    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}