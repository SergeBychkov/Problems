//https:

#include <print>
#include <vec_tor>
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

  vector<int> vec_;

  void inOrderTraversal(Node* root) {
    if (root != nullptr) {
      inOrderTraversal(root->left);
      vec_.push_back(root->data);
      inOrderTraversal(root->right);
    }
  }


  bool checkBST(Node* root) {
    vec_.clear();
    if (root != nullptr) {
      inOrderTraversal(root->left);
      vec_.push_back(root->data);
      inOrderTraversal(root->right);
    }
    //Print::printVector(vec_);
    for (size_t i = 0; i < vec_.size() - 1; i++) {
      if (vec_[i] >= vec_[i + 1])
        return false;
    }
    return true;
  }

}



void main() {
  try {
    println("Is This a Binary Search Tree started ...\n");

    Node* root = new Node(); 
    root->data = 3;

    root->left = new Node();
    root->left->data = 5;
    root->right = new Node(); 
    root->right->data = 2;

    root->left->left = new Node();
    root->left->left->data = 1;
    root->left->right = new Node();
    root->left->right->data = 4;

    root->right->left = new Node();
    root->right->left ->data = 6;

    println("checkBST = {}", checkBST(root));

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}