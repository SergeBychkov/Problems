//There are n children who want to go to a Ferris wheel, and your task is to find a gondola for each child.
//Each gondola may have one or two children in it, and in addition, the total weight in a gondola may not exceed x.You know the weight of every child.
//What is the minimum number of gondolas needed for the children ?
//Input
//The first input line contains two integers n and x : the number of children and the maximum allowed weight.
//The next line contains n integers p_1, p_2, \ldots, p_n: the weight of each child.
//Output
//Print one integer : the minimum number of gondolas.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le x \le 10 ^ 9
//1 \le p_i \le x
//
//Example
//Input :
//4 10
//7 2 3 9
//
//Output :
//  3

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include "random_utils.h"
using namespace std;

namespace {
  class FerrisWheel {
  public:

    FerrisWheel(int maxWeight, vector<int> children) : maxWeight_{maxWeight}, children_{children.begin(), children.end()} {}


    int work(bool verbose = false) {
      int result{};
      while (!children_.empty()) {
        if (verbose)
          printChildren();
        auto lastIter = --children_.end();
        auto last = *lastIter;
       
        if (last > maxWeight_)
          return -1;
        else if (last == maxWeight_) {
          result++;
          children_.erase(lastIter);
          continue;
        }

        if (children_.size() == 1) {
          result++;
          break;
        }

        int maxWeightFor2nd = maxWeight_ - last;
        bool is2ndFound{false};
        auto for2ndIter = children_.lower_bound(maxWeightFor2nd);
        if (for2ndIter != children_.end()) { // имеется предыдущий с большим или равным maxWeightFor2nd
          auto it = for2ndIter;
          while (true) {
            if (*it <= maxWeightFor2nd && it != lastIter) {
              is2ndFound = true;
              break;
            }
            if (it == children_.begin())
              break;
            it--;
          }
          if (is2ndFound) {
            children_.erase(it);
          }
        } else {  // предыдущие меньше maxWeightFor2nd
          auto temp = lastIter;
          children_.erase(--temp);
        }
        children_.erase(lastIter);
        result++;
      }
      return result;
    }



    void printChildren() {
      print("children: ");
      for (auto item : children_) {
        print("{}, ", item);
      }
      println("");
    }


    static void printVector(vector<int> children) {
      print("children: ");
      for (auto item : children) {
        print("{}, ", item);
      }
      println("");
    }


  private:
    int maxWeight_;
    multiset<int> children_;
  };



  void check(int maxWeight, vector<int> children, int expected) {
    FerrisWheel ferr(maxWeight, children);
    int result = ferr.work();
    if (result != expected) {
    FerrisWheel::printVector(children);
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }



  void autoCheck() {
    const int n = 100'000;
    for (int maxWeight = 10000; maxWeight >= 10; maxWeight /= 10) {
      auto rnd = Random::createRandomIntGenerator(1, maxWeight);
      vector<int> children;
      children.reserve(n);
      int cnt = 1;
      int expected = 0;
      while (cnt <= n) {
        int mass1st = rnd();
        children.push_back(mass1st);
        cnt++;
        int mass2st = maxWeight - mass1st;
        if (mass2st > 0) {
          children.push_back(mass2st);
          cnt++;
        }
        expected++;
      }
      check(maxWeight, children, expected);
    }
  }
}



void demo_FerrisWheel() {
  try {
    println("FerrisWheel started ...");

    int maxWeight = 10;
    vector<int> children{7, 2, 3, 9};
    FerrisWheel ferr(maxWeight, children);
    auto result = ferr.work(true);
    println("result = {}", result);
    

    check(10, {9}, 1);
    check(10, {10}, 1);
    check(10, {11}, -1);
    
    check(10, {2, 3}, 1);
    check(10, {2, 3, 4}, 2); 
    check(10, {2, 3, 4, 4}, 2); 
    check(10, {2, 3, 4, 4, 4}, 3); 
    

    check(10, {10, 9}, 2);
    check(10, {10, 9, 3, 2}, 3); 
    check(10, {7, 2, 3, 9}, 3);
    check(10, {1, 1, 1, 1, 1, 5}, 3);
    check(10, {1, 1, 1, 1, 4, 5}, 3);
    check(10, {1, 1, 1, 1, 5, 5}, 3);

    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}