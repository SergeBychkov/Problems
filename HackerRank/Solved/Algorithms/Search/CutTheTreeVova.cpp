//https://www.hackerrank.com/challenges/cut-the-tree/problem?isFullScreen=true

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

int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    int res{ INT32_MAX };
    int sum = accumulate(data.begin(), data.end(), 0);
    map<int, set<int>> node_neighbor;
    map<int, set<int>> link_node;

    for (auto& edge : edges) {
        int n1 = edge[0];
        int n2 = edge[1];
        node_neighbor[n1].insert(n2);
        node_neighbor[n2].insert(n1);
    }
    for (auto& [n, neighbors] : node_neighbor) {
        link_node[neighbors.size()].insert(n);
    }

    while (node_neighbor.size() > 0) {
        int n = *link_node[1].begin();
        int m = *node_neighbor[n].begin();
        link_node[1].erase(n);

        res = min(res, abs(sum - data[n - 1] - data[n - 1]));

        // n:{m} and m:{n,...}
        // remove n from neighbors of m
        int m_neighbor_size = node_neighbor[m].size();
        node_neighbor[m].erase(n);
        if (node_neighbor[m].size() == 0) node_neighbor.erase(m);
        // remove n from node_neighbor
        node_neighbor.erase(n);

        // merge n's data to m's data
        data[m - 1] += data[n - 1];

        link_node[m_neighbor_size].erase(m);
        if (m_neighbor_size > 1) link_node[m_neighbor_size - 1].insert(m);
    }
    return res;
}

void check(vector<int> data, vector<vector<int>> edges, int expected) {
    auto result = cutTheTree(data, edges);
    if (result != expected) {
        println("Error with result = {}, expected = {}", result, expected);
        throw exception("Error!");
    }
}

}


void demo_CutTheTreeVova() {
  try {
	println("demo_CutTheTreeVova started ...\n");

    vector<int> data = { 100, 200, 100, 500, 100, 600 };
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {2, 5}, {4, 5}, {5, 6} };

    check(data, edges, 400);

  } catch (exception ex) {
	println("{}", ex.what());
  }
}