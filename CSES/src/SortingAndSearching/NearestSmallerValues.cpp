//Given an array of n integers, your task is to find for each array position the nearest position to its left having a smaller value.
//Input
//The first input line has an integer n : the size of the array.
//The second line has n integers x_1, x_2, \dots, x_n: the array values.
//Output
//Print n integers : for each array position the nearest position with a smaller value.If there is no such position, print 0.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le x_i \le 10 ^ 9
//
//Example
//Input :
//8
//2 5 1 4 8 3 2 5
//
//Output :
//0 1 0 3 4 3 3 7

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  struct Value {
    int x_{};
    mutable int idx_{}; //for changing! 
  };

  auto valueComparator = [](const Value& a, const Value& b) { return a.x_ < b.x_; };

  class NearestSmallerValues {
  public:

    NearestSmallerValues(vector<int> x) : vecX_{x} {}


    vector<int> work(bool verbose = false) {
      vector<int> result{};
      int nearestSmaller{};
      for (int i = 0; i < vecX_.size(); i++) {
        int& x = vecX_[i];

        if (i == 0) {
          result.push_back(0);
          priorsX_.insert(Value{x, 0});
          continue;
        }

        auto it = priorsX_.lower_bound(Value{x, i});
        if (it == priorsX_.end()) { //not found greater or equal x 
          result.push_back((*--priorsX_.end()).idx_ + 1);
        } else {
          if (it == priorsX_.begin()) {
            result.push_back(0);
          } else {
            result.push_back((*--it).idx_ + 1);
          }
        }

        auto [itInsert, isNewInserted] = priorsX_.insert(Value{x, i});
        if (!isNewInserted)
          (*itInsert).idx_ = i;

        if (itInsert != priorsX_.end()) { //detete all greaters
          itInsert++;
          priorsX_.erase(itInsert, priorsX_.end());
        }

        if (verbose)
          printInfo();
      }
      return result;
    }


  private:
    void printInfo() {
      print("priorsX_: ");
      for (auto item : priorsX_) {
        print("({} - {}) , ", item.x_, item.idx_);
      }
      println("");
    }


    vector<int> vecX_;
    set<Value, decltype(valueComparator)> priorsX_;
  };



  void check(vector<int> x, vector<int> expected) {
    NearestSmallerValues nearestSmallerValues(x);
    auto result = nearestSmallerValues.work();
    if (result != expected) {
      print("x     :");  Print::printVector(x, 3);
      print("result  :"); Print::printVector(result, 3);
      print("expected:"); Print::printVector(expected, 3);
      throw exception("Error!");
    }
  }
}



void demo_NearestSmallerValues() {
  try {
    println("demo_NearestSmallerValues started ...\n");

    vector<int> x{2, 5, 1, 4, 8, 3, 2, 5};
    NearestSmallerValues nearestSmallerValues(x);
    auto result = nearestSmallerValues.work(true);
    print("x     :");  Print::printVector(x, 3);
    print("result:"); Print::printVector(result, 3);

    check({2, 5, 1, 4, 8, 3, 2, 5}, {0, 1, 0, 3, 4, 3, 3, 7});

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}