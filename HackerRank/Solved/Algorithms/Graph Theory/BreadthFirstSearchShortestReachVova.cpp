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

vector<int> bfs(int n, int m, vector<vector<int>> edges, int s, bool verbose = false) {
  vector<int> res(n - 1, -1);
  unordered_set<int> visited;
  vector<vector<int>> neighbors(n + 1);

  for (auto& edge : edges) {
    neighbors[edge[0]].push_back(edge[1]);
    neighbors[edge[1]].push_back(edge[0]);
  }

  visited.insert(s);
  deque<pair<int, int>> next_moves;
  for (auto n : neighbors[s]) next_moves.push_back({ n, 1 });

  while (next_moves.size() > 0) {
    auto [next, distance] = next_moves.front();
    next_moves.pop_front();

    if (visited.find(next) != visited.end()) continue;

    visited.insert(next);

    res[next < s ? next - 1 : next - 2] = 6 * distance;

    for (auto n : neighbors[next]) next_moves.push_back({ n, 1 + distance });
  }
  return res;
}


  void check(int n, int m, vector<vector<int>> edges, int s, vector<int> expected, bool verbose = false) {
    if (verbose) {
      println("checking ...");
    }
    auto result = bfs(n, m, edges, s, verbose);
    if (result != expected) {
      Print::printVector(result);
      Print::printVector(expected);
      println("Error");
      throw exception("Error!");
    }
  }
}

void main() {
  try {
    println("demo_QqqVova started ...\n");

    vector<vector<int>> edges;
    edges.push_back({ 1, 2 });
    edges.push_back({ 1, 3 });
    check(3, 2, edges, 1, {6, 6}, true);


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}