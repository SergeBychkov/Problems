//https://www.hackerrank.com/challenges/common-child/problem?isFullScreen=true

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  class CommonChild {
  public:
    CommonChild(const string& s1, const string& s2) : s1_{s1}, s2_{s2} {
      size_ = min(s1.size(), s2.size());
      mat_.resize(size_, vector<int>(size_, 0));
    }



    int work(bool verbose = false) {
      int result{};
      mat_[0][0] = (s1_[0] == s2_[0]) ? 1 : 0;
      for (size_t j = 1; j < size_; j++) {
        if (s1_[j] == s2_[0] || mat_[0][j - 1] == 1 || mat_[0][0] == 1)
          mat_[0][j] = 1;
      }
      for (size_t i = 1; i < size_; i++) {
        if (s2_[i] == s1_[0] || mat_[i - 1][0] == 1 || mat_[0][0] == 1)
          mat_[i][0] = 1;
      }

      for (size_t i = 1; i < size_; i++) {
        char fixChar = s2_[i];
        for (size_t j = 1; j < size_; j++) {
          if (s1_[j] == fixChar) {
            mat_[i][j] = mat_[i - 1][j - 1] + 1;
          } else {
            mat_[i][j] = max(mat_[i - 1][j], mat_[i][j - 1]);
          }
        }
      }
      if (verbose)
        printMatrix();

      return mat_[size_ - 1][size_ - 1];
    }



    //for site
    int commonChild(string s1_, string s2_) {
      int size_ = min(s1_.size(), s2_.size());
      vector<vector<int>> mat_;
      mat_.resize(size_, vector<int>(size_, 0));
      mat_[0][0] = (s1_[0] == s2_[0]) ? 1 : 0;
      for (size_t j = 1; j < size_; j++) {
        if (s1_[j] == s2_[0] || mat_[0][j - 1] == 1 || mat_[0][0] == 1)
          mat_[0][j] = 1;
      }
      for (size_t i = 1; i < size_; i++) {
        if (s2_[i] == s1_[0] || mat_[i - 1][0] == 1 || mat_[0][0] == 1)
          mat_[i][0] = 1;
      }

      for (size_t i = 1; i < size_; i++) {
        char fixChar = s2_[i];
        for (size_t j = 1; j < size_; j++) {
          if (s1_[j] == fixChar) {
            mat_[i][j] = mat_[i - 1][j - 1] + 1;
          } else {
            mat_[i][j] = max(mat_[i - 1][j], mat_[i][j - 1]);
          }
        }
      }
      return mat_[size_ - 1][size_ - 1];
    }



    void printMatrix() {
      print("  ");
      for (auto& item : s1_) {
        print("{} ", item);
      }
      println("");

      int cntRow = 0;
      for (auto& row : mat_) {
        print("{}|", s2_[cntRow]);
        for (auto& item : row) {
          print("{} ", item);
        }
        println("");
        cntRow++;
      }
      println("");
    }


  private:
    string s1_;
    string s2_;
    int size_;
    vector<vector<int>> mat_;
  };



  void check(const string& s1, const string& s2, int expected, bool verbose = false) {
    CommonChild solution(s1, s2);
    auto result = solution.work(verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_CommonChild() {
  try {
    println("demo_CommonChild started ...\n");

    //CommonChild solution("abcd", "abdc");
    //auto result = solution.work();
    //println("result = {}", result);

    check("AA", "BB", 0, true);
    check("abcd", "abdc", 3);
    check("HARRY", "SALLY", 2);
    check("SHINCHAN", "NOHARAAA", 3, true);
    check("ABCDEF", "FBDAMN", 2, true);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}