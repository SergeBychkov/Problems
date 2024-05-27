//There is a list of n numbers and two players who move alternately.On each move, a player removes either the first or last number from the list, and their score increases by that number.Both players try to maximize their scores.
//What is the maximum possible score for the first player when both players play optimally ?
//Input
//The first input line contains an integer n : the size of the list.
//The next line has n integers x_1, x_2, \ldots, x_n: the contents of the list.
//Output
//Print the maximum possible score for the first player.
//Constraints
//
//1 \le n \le 5000
//- 10 ^ 9 \le x_i \le 10 ^ 9
//
//Example
//Input :
//4
//4 5 1 3
//
//Output :
//  8

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
  class RemovalGame {
  public:
    struct Indexes {
      int idx1;
      int idx2;
    };

    struct IndexesHash {
      //constexpr size_t operator()(Indexes idxs) const {
      size_t operator()(Indexes idxs) const {
        size_t h1 = hash<int>{}(idxs.idx1);
        size_t h2 = hash<int>{}(idxs.idx2);
        return h1 ^ (h2 << 1);
      }
    };

    struct IndexesEq {
      constexpr bool operator()(Indexes a, Indexes b) const {
        return a.idx1 == b.idx1 && a.idx2 == b.idx2;
      }
    };


    RemovalGame(vector<int> vec) : vec_{vec} {}


    int solveRecurs(int idx1, int idx2) { //can be accelerated with caching


      //unordered_map<Indexes, int, IndexesHash, IndexesEq> cache;


      if (idx1 + 1 == idx2) {
        return max({vec_[idx1], vec_[idx2]});
      }

      int solv1 = cache_[Indexes{idx1 + 1, idx2}];
      if (solv1 == 0) {
        solv1 = solveRecurs(idx1 + 1, idx2);
        cache_[Indexes{idx1 + 1, idx2}] = solv1;
      }

      int solv2 = cache_[Indexes{idx1, idx2 - 1}];
      if (solv2 == 0) {
        solv2 = solveRecurs(idx1, idx2 - 1);
        cache_[Indexes{idx1, idx2 - 1}] = solv2;
      }

      int sumAll = prefSums_[idx2] - ((idx1 != 0) ? prefSums_[idx1 - 1] : 0);
      int res1 = sumAll - solv1;
      int res2 = sumAll - solv2;
      return max(res1, res2);
    }

    int workRecurs() {
      int size = vec_.size();
      prefSums_.resize(size);
      int sum = 0;
      for (size_t i = 0; i < size; i++) {
        sum += vec_[i];
        prefSums_[i] = sum;
      }
      return solveRecurs(0, vec_.size() - 1);
    }



    int workThe_hyp0() { //the fastest!
    https://github.com/the-hyp0cr1t3/CC/blob/master/CSES/Dynamic%20Programming/Removal%20Game.cpp
      int cur = 1, ans = 0;
      deque<int> v;
      int size = vec_.size();
      for (int i = 0; i < size; i++) {
        v.push_back(vec_[i]);
        while ((int)v.size() > 2) {
          int x = v[(int)v.size() - 3];
          int y = v[(int)v.size() - 2];
          int z = v[(int)v.size() - 1];
          if (x > y or y < z) break;
          v.pop_back(); v.pop_back(); v.pop_back();
          v.push_back(x + z - y);
        }
      }
      while (!v.empty()) {
        ans += max(v.front(), v.back()) * cur;
        if (v.front() > v.back()) v.pop_front();
        else v.pop_back();
        cur = -cur;
      }
      return accumulate(vec_.begin(), vec_.begin() + size, 0) + ans >> 1;
    }




    int solveNoob(int i, int j) {
      if (i > j)
        return 0;

      if (dp_[i][j] != -1)
        return dp_[i][j];

      int op1 = vec_[i] + min(solveNoob(i + 2, j), solveNoob(i + 1, j - 1));
      int op2 = vec_[j] + min(solveNoob(i + 1, j - 1), solveNoob(i, j - 2));
      return dp_[i][j] = max(op1, op2);
    }

    int workNoob() {
      //https://github.com/noob-hu-yaar/CSES-Problem-set-solutions-DP-/blob/master/code_TD(Removal%20Game).cpp
      return solveNoob(0, vec_.size() - 1);
    }


  private:
    vector<int> vec_;
    vector<int> prefSums_;
    unordered_map<Indexes, int, IndexesHash, IndexesEq> cache_;
    vector<vector<int>> dp_{5005, vector<int>(5005, -1)};


    void printPair(pair<int, int> pair) {
      print("[{}, {}]", pair.first, pair.second);
    }
  };


  void autoCheck() {
    //int size = 5; //losses != 0!
    int size = 20;  //losses often == 0
    int nTests = 100;

    int nWins{}, nLosses{}, nDraws{};
    for (size_t i = 0; i < nTests; i++) {
      auto vec = Random::getRandomIntVector(size, 1, 10, true);
      //auto vec = Random::getRandomIntVector(size, 1, 10);
      RemovalGame removalGame(vec);
      int result1 = removalGame.workRecurs();
      int result2 = removalGame.workThe_hyp0();
      int result3 = removalGame.workNoob();
      if (result1 != result2 || result2 != result3 || result1 != result3) {
        Print::printVector(vec, 3, 0, vec.size());
        println("result1 = {}, result2 = {}, result3 = {}", result1, result2, result3);
        throw exception("Error in autoCheck!");
      }
      int sum = accumulate(vec.begin(), vec.end(), 0);
      if (result1 > sum / 2)
        nWins++;
      else if (result1 < sum / 2)
        nLosses++;
      else
        nDraws++;
    }
    println("\nwins = {}, losses = {}, draws = {}", nWins, nLosses, nDraws);
    println("autoCheck passed!");
  }



  void bench() {
    println("\nBenchmarking:");
    int size = 1000;
    auto vec = Random::getRandomIntVector(size, 1, 10);
    RemovalGame removalGame(vec);

    auto t1 = chrono::high_resolution_clock::now();
    auto result = removalGame.workRecurs();
    auto t2 = chrono::high_resolution_clock::now();
    println("result = {}", result);
    println("duration workRecurs  : {} sec", (double)(t2 - t1).count() / 1'000'000'000);


    t1 = chrono::high_resolution_clock::now();
    result = removalGame.workThe_hyp0();
    t2 = chrono::high_resolution_clock::now();
    println("result = {}", result);
    println("duration workThe_hyp0: {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    t1 = chrono::high_resolution_clock::now();
    result = removalGame.workNoob();
    t2 = chrono::high_resolution_clock::now();
    println("result = {}", result);
    println("duration workNoob    : {} sec", (double)(t2 - t1).count() / 1'000'000'000);
  }
}



void demo_RemovalGame() {
  try {
    println("demo_RemovalGame started ...\n");

    vector<int> vec{6, 6, 8, 9};
    RemovalGame removalGame(vec);
    Print::printVector(vec, 3);
    auto result = removalGame.workRecurs();
    println("result workRecurs   = {}", result);
    auto result2 = removalGame.workThe_hyp0();
    println("result workThe_hyp0 = {}", result2);
    auto result3 = removalGame.workNoob();
    println("result workNoob     = {}", result3);


    autoCheck();
    bench();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}