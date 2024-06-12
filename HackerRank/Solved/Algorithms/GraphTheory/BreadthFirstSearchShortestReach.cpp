//https://www.hackerrank.com/challenges/bfsshortreach/problem?isFullScreen=true

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
  struct Node {
    int id{};
    int dist{};
  };


  struct Edge {
    int first{};
    int second{};
  };


  struct CompareEdge {
    bool operator()(const Edge& a, const Edge& b) const {
      return a.first < b.first;
    }
  };


  void printEdges(const vector<vector<int>>& edges) {
    for (const auto& item : edges)
      print("[{} - {}], ", item[0], item[1]);
    println("");
  }


  void printSet(multiset<Edge, CompareEdge> edgeSet) {
    for (const auto& item : edgeSet)
      print("[{} - {}], ", item.first, item.second);
    println("");
  }


  //Serg's solution - much slower!!!
  vector<int> bfs(int n, int m, vector<vector<int>> edges, int s, bool verbose = false) {
    vector<int> result;
    vector<Node> nodes(n + 1);
    multiset<Edge, CompareEdge> edgeSet;
    for (size_t i = 1; i < n + 1; i++) {
      nodes[i].id = i;
      nodes[i].dist = (i == s) ? 0 : -1;
    }
    for (size_t i = 0; i < m; i++) {
      edgeSet.insert({edges[i][0], edges[i][1]});
      edgeSet.insert({edges[i][1], edges[i][0]});
    }
    if (verbose) {
      println("n = {}, s = {}", n, s);
      printSet(edgeSet);
    }

    deque<int> stack;
    stack.push_back(s);
    while (!stack.empty()) {
      int curr = stack.back();
      int currDist = nodes[curr].dist;
      stack.pop_back();
      if (verbose) {
        println("curr = {}, currDist = {}", curr, currDist);
      }

      auto it = edgeSet.lower_bound(Edge{curr, 0});
      while (it != edgeSet.end() && it->first == curr) {
        int foundNodeIdx = it->second;
        if (nodes[foundNodeIdx].dist == -1) {
          nodes[foundNodeIdx].dist = currDist + 1;
          stack.push_front(foundNodeIdx);
          if (verbose) {
            print("   found = {}, ", foundNodeIdx);
          }
        }
        ++it;
      }
      if (verbose) {
        println("");
      }
    }

    for (size_t i = 1; i < n + 1; i++) {
      if (i != s) {
        int dist = nodes[i].dist;
        result.push_back((dist != -1) ? 6 * dist : dist);
      }
    }
    if (verbose) {
      print("result: "); Print::printVector(result);
    }
    return result;
  }


  
  //much faster!!!
  vector<int> bfsVova(int n, int m, vector<vector<int>> edges, int s, bool verbose = false) {
    vector<int> res(n - 1, -1);
    unordered_set<int> visited;
    vector<vector<int>> neighbors(n + 1);

    for (auto& edge : edges) {
      neighbors[edge[0]].push_back(edge[1]);
      neighbors[edge[1]].push_back(edge[0]);
    }

    visited.insert(s);
    deque<pair<int, int>> next_moves;
    for (auto i : neighbors[s])
      next_moves.push_back({i, 1});

    while (next_moves.size() > 0) {
      auto [next, distance] = next_moves.front();
      next_moves.pop_front();

      if (visited.find(next) != visited.end())
        continue;

      visited.insert(next);

      res[next < s ? next - 1 : next - 2] = 6 * distance;

      for (auto i : neighbors[next])
        next_moves.push_back({i, 1 + distance});
    }
    return res;
  }



  void check(int n, int m, vector<vector<int>> edges, int s, vector<int> expected, bool verbose = false) {
    auto result1 = bfs(n, m, edges, s, verbose);
    if (result1 != expected) {
      println("Error in bfs with n = {}, m = {}, s = {}", n, m, s);
      print("result1: "); Print::printVector(result1);
      throw exception("Error!");
    }
    auto result2 = bfsVova(n, m, edges, s, verbose);
    if (result2 != expected) {
      println("Error in bfsVovawith n = {}, m = {}, s = {}", n, m, s);
      print("result2: "); Print::printVector(result2);
      throw exception("Error!");
    }
  }



  void checkTwo(int n, int m, vector<vector<int>> edges, int s, bool verbose = false) {
    auto result1 = bfs(n, m, edges, s, verbose);
    auto result2 = bfsVova(n, m, edges, s, verbose);
    if (result1 != result2) {
      println("Error with n = {}, m = {}, s = {}", n, m, s);
      printEdges(edges);
      print("result1: "); Print::printVector(result1);
      print("result2: "); Print::printVector(result2);
      throw exception("Error in checkTwo!");
    }
  }



  void autoCheck() {
    int nMax = 10;
    for (size_t n = 4; n <= nMax; n++) {
      int m = n * (n - 1) / 4;
      auto rnd = Random::createRandomIntGenerator(1, n);
      vector<vector<int>> edges;
      for (size_t i = 0; i < m; i++) {
        edges.push_back({rnd(), rnd()});
      }
      for (size_t s = 1; s <= n; s++) {
        auto result1 = bfs(n, m, edges, s);
        auto result2 = bfsVova(n, m, edges, s);
        if (result1 != result2) {
          println("Error with n = {}, m = {}, s = {}", n, m, s);
          printEdges(edges);
          print("result1: "); Print::printVector(result1);
          print("result2: "); Print::printVector(result2);
          throw exception("Error in autoCheck!");
        }
      }
    }
  }


   
  void bench() {
    int n = 5'000;
    int m = n * (n - 1) / 4;
    int s = 1;
    auto rnd = Random::createRandomIntGenerator(1, n);
    vector<vector<int>> edges;
    for (size_t i = 0; i < m; i++) {
      edges.push_back({rnd(), rnd()});
    }

    auto t1 = chrono::high_resolution_clock::now();
    auto result1 = bfs(n, m, edges, s);
    auto t2 = chrono::high_resolution_clock::now();
    println("bfs    : {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    t1 = chrono::high_resolution_clock::now();
    auto result2 = bfsVova(n, m, edges, s);
    t2 = chrono::high_resolution_clock::now();
    println("bfsVova: {} sec", (double)(t2 - t1).count() / 1'000'000'000);

    println("{}", result1[0] == result2[0]);
  }
}



void main() {
  try {
    println("BreadthFirstSearchShortestReach started ...\n");

    check(5, 3, {{1, 2}, {1, 3}, {3, 4}}, 1, {6, 6, 12, -1});
    check(4, 2, {{1, 2}, {1, 3}}, 1, {6, 6, -1});
    check(3, 1, {{2, 3}}, 2, {-1, 6});

    //checkTwo(8, 8, {{6, 7}, {5, 7}, {4, 5}, {6, 4}, {4, 3}, {8, 1}, {8, 3}, {8, 7}}, 1, true);

    autoCheck();

    bench();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}