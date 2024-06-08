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

  struct Node {
    int data{};
    Node* left{};
    Node* right{};
  };


  Node* insert(Node* root, int data) {
    if (root == NULL) {
      return new Node{data, nullptr, nullptr};
    } else {
      Node* cur;
      if (data <= root->data) {
        cur = insert(root->left, data);
        root->left = cur;
      } else {
        cur = insert(root->right, data);
        root->right = cur;
      }
      return root;
    }
  }



  void printVec(const vector<Node*> vec) {
    for (const auto& el : vec) {
      print("{:8}", el->data);
    }
    println("");
  }



  vector<Node*> findAllBefore(Node* root, int value) {
    vector<Node*> vec;
    while (root != nullptr) {
      if (root->data == value) {
        vec.push_back(root);
        return vec;
      } else if (root->data < value) {
        vec.push_back(root);
        root = root->right;
      } else {
        vec.push_back(root);
        root = root->left;
      }
    }
    return vec;
  }



  Node* lca(Node* root, int v1, int v2, bool verbose = false) {
    Node* result{};
    auto vec1 = findAllBefore(root, v1);
    printVec(vec1);
    auto vec2 = findAllBefore(root, v2);
    printVec(vec2);

    for (int i = 0; i < vec1.size() && i < vec2.size(); i++) {
      if (vec1[i] == vec2[i]) {
        result = vec1[i];
      } else {
        break;
      }
    }
    return result;
  }



  void check(vector<int> data, int v1, int v2, int expected, bool verbose = false) {
    Node* root = nullptr;
    for (auto item : data) {
      root = insert(root, item);
    }

    auto result = lca(root, v1, v2, verbose);
    if (result->data != expected) {
      println("Error with result = {}, expected = {}", result->data, expected);
      throw exception("Error!");
    }
  }
}



void main() {
  try {
    println("LowestCommonAncestor started ...\n");

    check({4, 2, 3, 1, 7, 6}, 1, 7, 4, true);
    check({2, 1, 3, 4, 5, 6}, 3, 6, 3, true);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}