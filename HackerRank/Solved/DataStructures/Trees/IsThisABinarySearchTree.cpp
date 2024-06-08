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
      return new Node();
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

  vector<int> vec;

  void inOrderTraversal(Node* root) {
    if (root != nullptr) {
      inOrderTraversal(root->left);
      vec.push_back(root->data);
      inOrderTraversal(root->right);
    }
  }


  bool checkBST(Node* root) {
    vec.clear();
    if (root != nullptr) {
      inOrderTraversal(root->left);
      vec.push_back(root->data);
      inOrderTraversal(root->right);
    }
    //Print::printVector(vec);
    for (size_t i = 0; i < vec.size() - 1; i++) {
      if (vec[i] > vec[i + 1])
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

    //2
    //1 2 2 4 5 6 7
    //Expected Output
    //No


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}