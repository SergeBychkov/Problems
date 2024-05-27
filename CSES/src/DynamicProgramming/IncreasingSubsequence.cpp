//You are given an array containing n integers.Your task is to determine the longest increasing subsequence in the array, i.e., the longest subsequence where every element is larger than the previous one.
//A subsequence is a sequence that can be derived from the array by deleting some elements without changing the order of the remaining elements.
//Input
//The first line contains an integer n : the size of the array.
//After this there are n integers x_1, x_2, \ldots, x_n: the contents of the array.
//Output
//Print the length of the longest increasing subsequence.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le x_i \le 10 ^ 9
//
//Example
//Input :
//8
//7 3 5 3 6 2 9 8
//
//Output :
//  4

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  struct Point {
    int value_{};
    mutable int prevLen_{};
  };

  auto pointComparator = [](const Point& a, const Point& b) { return a.value_ < b.value_; };

  class IncreasingSubsequence {
  public:

    IncreasingSubsequence(vector<int> vec) : vec_{vec} {}


    int work(bool verbose = false) { //does not work - delete!
      int result{};
      set<Point, decltype(pointComparator)> seq;
      seq.insert(Point{vec_[0], 1});
      int size = vec_.size();
      for (int i = 1; i < size; i++) {
        auto curr = Point{vec_[i], 1};
        auto it = seq.lower_bound(curr);

        if (it != seq.begin()) {

          int prevMax = 0;
          for_each(seq.begin(), it, [&](const Point& pt) {
            if (pt.prevLen_ > prevMax) prevMax = pt.prevLen_;
            });
          curr.prevLen_ = prevMax + 1;
          seq.insert(curr);
          //seq.erase(it);
        } else {
          if ((*it).value_ - curr.value_ > 1)
            seq.insert(curr);
        }
        if (verbose) {
          print("i = {};  ", i);
          printSet(seq);
        }
      }
      ranges::for_each(seq, [&](const Point& pt) {
        if (pt.prevLen_ > result) result = pt.prevLen_;
        });
      return result;
    }



    vector<int> work_cp_algorithms_ON2(bool verbose = false) {
      //https://cp-algorithms.com/sequences/longest_increasing_subsequence.html
      //this is a solution with O(N*N)
      //see solution with O(N*log(N))
      int n = vec_.size();
      vector<int> d(n, 1), p(n, -1);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
          if (vec_[j] < vec_[i] && d[i] < d[j] + 1) {
            d[i] = d[j] + 1;
            p[i] = j;
          }
        }
      }

      int ans = d[0], pos = 0;
      for (int i = 1; i < n; i++) {
        if (d[i] > ans) {
          ans = d[i];
          pos = i;
        }
      }

      vector<int> subseq;
      while (pos != -1) {
        subseq.push_back(vec_[pos]);
        pos = p[pos];
      }
      reverse(subseq.begin(), subseq.end());
      return subseq;
    }



    int workJonathan(bool verbose = false) {
      //https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Dynamic%20Programming/Increasing%20Subsequence.cpp
      //https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
      multiset<int> seq;
      for (int i = 0; i < vec_.size(); i++) {
        seq.insert(vec_[i]);
        auto it = seq.lower_bound(vec_[i]);
        it++;
        if (it != seq.end())
          seq.erase(it);
        if (verbose) {
          println("i = {}, size = {}", i, seq.size());
          Print::printSet(seq, 3);
          println("------------------------------------------------------------------");
        }
      }
      return seq.size();
    }



  private:
    vector<int> vec_;

    void printSet(const set<Point, decltype(pointComparator)>& seq) {
      for (auto& item : seq) {
        print("({}, {}), ", item.value_, item.prevLen_);
      }
      println("");
    }
  };



  //void check(vector<int> vec, int expected) {
  //  IncreasingSubsequence increasingSubsequence(vec);
  //  auto result = increasingSubsequence.work();
  //  if (result != expected) {
  //    println("Error with result = {}, expected = {}", result, expected);
  //    throw exception("Error!");
  //  }
  //}



  void autoCheck() {
    //int size = 1000;
    int size = 10;
    int nTests = 20;
    for (size_t i = 0; i < nTests; i++) {
      auto vec = Random::getRandomIntVector(size, 0, 10, true);
      //auto vec = Random::getRandomIntVector(size, 0, 100);
      IncreasingSubsequence increasingSubsequence(vec);
      auto result1 = increasingSubsequence.work_cp_algorithms_ON2().size();
      auto result2 = increasingSubsequence.workJonathan();
      if (result1 != result2) {
        Print::printVector(vec, 4, 0, vec.size());
        println("\nresult1 = {}, result2 = {}", result1, result2);
        throw exception("Error in autoCheck!");
      }
    }
    println("autoCheck passed!");
  }



  //void demoHelper(vector<int> vec) {
  //  IncreasingSubsequence increasingSubsequence(vec);
  //  Print::printVector(vec, 3, 0, vec.size(), true);
  //  println("");
  //  auto result = increasingSubsequence.workJonathan(true);
  //  println("result workJonathan = {}", result);
  //}



  void learningDemo() {
    vector<int> vec{7, 3, 5, 3, 6, 2, 9, 8};
    IncreasingSubsequence increasingSubsequence(vec);
    Print::printVector(vec, 3, 0, vec.size(), true);
    auto resultVec = increasingSubsequence.work_cp_algorithms_ON2(true);
    Print::printVector(resultVec, 3);
    println("result work_cp_algorithms_ON2 = {}", resultVec.size());
    auto result = increasingSubsequence.workJonathan();
    println("result workJonathan           = {}", result);
  }
}



void demo_IncreasingSubsequence() {
  try {
    println("demo_IncreasingSubsequence started ...\n");

    learningDemo();

    //check({1, 1}, 1);
    //check({1, 2}, 2);
    //check({2, 1}, 1);
    //check({4, 1, 2, 3, 1}, 3);
    //check({1, 8, 1, 5, 2, 2, 6, 4, 10}, 4); 
    //check({6, 7, 6, 2, 3, 0, 4, 5, 7, 8}, 4); //bad


    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}