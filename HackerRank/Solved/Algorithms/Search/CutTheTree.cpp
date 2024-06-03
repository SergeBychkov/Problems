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

  struct Node {
    int id{};
    int prevNode{};
    int value{};
    int valueAccum{};
  };

  struct Edge {
    int node1{};
    int node2{};
  };


  void printNodes(vector<Node> nodes) {
    print("\nid        :");
    for (auto& node : nodes) {
      print("{:8}", node.id);
    }
    print("\nprevNode  :");
    for (auto& node : nodes) {
      print("{:8}", node.prevNode);
    }
    print("\nvalue     :");
    for (auto& node : nodes) {
      print("{:8}", node.value);
    }
    print("\nvalueAccum:");
    for (auto& node : nodes) {
      print("{:8}", node.valueAccum);
    }
    println("");
  }



  void printEdgesSet(multiset<Edge, bool(*)(const Edge&, const Edge&)> edgesSet) {
    for (auto& edge : edgesSet) {
      println("{} - {}", edge.node1, edge.node2);
    }
    println("");
  }



  int cutTheTree(vector<int> data, vector<vector<int>> edges, bool verbose = false) {
    int size = data.size();
    vector<Node> nodes(size);
    transform(data.begin(), data.end(), nodes.begin(), [i = 0](int value) mutable {
      return Node{i++, -1, value, value};
      });
    nodes[0].prevNode = -2;
    if (verbose) {
      printNodes(nodes);
    }

    std::multiset<Edge, bool(*)(const Edge&, const Edge&)> edgesSet([](const Edge& a, const Edge& b) {
      return a.node1 < b.node1;
      });
    for (auto& edge : edges) {
      edgesSet.insert({edge[0] - 1, edge[1] - 1});
      edgesSet.insert({edge[1] - 1, edge[0] - 1});
    }
    if (verbose) {
      printEdgesSet(edgesSet);
    }

    vector<vector<int>> levels;
    set<int> passedNodes;
    levels.push_back({0});
    passedNodes.insert(0);
    int currLevel = 0;

    while (true) {
      vector<int> newNodes;
      for (int currNode : levels[currLevel]) {
        Edge keyEdge;
        keyEdge.node1 = currNode;
        auto lower = edgesSet.lower_bound(keyEdge);
        auto upper = edgesSet.upper_bound(keyEdge);
        for (auto it = lower; it != upper; ++it) {
          auto edge = *it;
          //not works on site!
          //if (passedNodes.contains(edge.node2))
          //  continue;
          if (auto search = passedNodes.find(edge.node2); search != passedNodes.end()) {
            continue;
          }

          nodes[edge.node2].prevNode = edge.node1;
          newNodes.push_back(edge.node2);
          passedNodes.insert(edge.node2);
        }
      }
      if (!newNodes.empty()) {
        levels.push_back(newNodes);
      } else {
        break;
      }
      currLevel++;
    }


    for (int i = levels.size() - 1; i > 0; i--) {
      for (int node : levels[i]) {
        nodes[nodes[node].prevNode].valueAccum += nodes[node].valueAccum;
      }
    }
    if (verbose) {
      print("after:");
      printNodes(nodes);
    }

    int totalSum = accumulate(nodes.begin(), nodes.end(), 0, [](int sum, Node& node) {
      return sum + node.value;
      });
    int minDiff = INT_MAX;
    for(auto& node : nodes) {
      int diff = abs(totalSum - 2 * node.valueAccum);
      if (diff < minDiff) {
        minDiff = diff;
      }
    }
    return minDiff;
  }



  void check(vector<int> data, vector<vector<int>> edges, int expected, bool verbose = false) {
    if (verbose) {
      println("checking ...");
    }
    auto result = cutTheTree(data, edges, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_CutTheTree() {
  try {
    println("CutTheTree started ...\n");

    check({1, 2, 3, 4, 5, 6}, {{1, 2}, {1, 3}, {2, 6}, {3, 4}, {3, 5}}, 3, true);
    check({100, 200, 100, 500, 100, 600}, {{1, 2}, {2, 3}, {2, 5}, {4, 5}, {5, 6}}, 400, false);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}