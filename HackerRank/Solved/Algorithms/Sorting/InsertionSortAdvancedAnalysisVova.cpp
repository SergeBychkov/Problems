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
  int val;
  int number_to_right;
  Node* left;
  Node* right;
};

int64_t add_element(Node* root, int new_val) {
  if (new_val >= root->val) {
    root->number_to_right++;
    if (root->right == nullptr) {
      root->right = new Node{ new_val, 0, nullptr, nullptr };
      return 0;
    } else {
      return add_element(root->right, new_val);
    }
  }
  if (new_val < root->val) {
    if (root->left == nullptr) {
        root->left = new Node{ new_val, 0, nullptr, nullptr };
        return 1 + root->number_to_right;
    } else {
        return 1 + root->number_to_right + add_element(root->left, new_val);
    }
  }
  return 0;
}

// Solution with tree aproach, everything works but not optimal. It's O(n^2) in worst case
// Two tests timed out
 int64_t insertionSortWithTree(vector<int> arr, bool verbose = false) {
    int64_t res{ 0 };

    Node* root = new Node{ arr[0], 0, nullptr, nullptr };
    for (int i{ 1 }; i < arr.size(); i++) {
      res += add_element(root, arr[i]);
    }

    return res;
  }


 int64_t merge(std::vector<int>& vec, std::vector<int>& temp, int l, int m, int r) {
   int64_t inv_count{ 0 };
   int i{ l }, j{ m + 1 }, k{ l };

   while (i <= m && j <= r) {
     if (vec[i] <= vec[j]) {
       temp[k++] = vec[i++];
     }
     else {
       temp[k++] = vec[j++];
       inv_count += (m - i + 1);
     }
   }

   while (i <= m) {
     temp[k++] = vec[i++];
   }

   while (j <= r) {
     temp[k++] = vec[j++];
   }

   for (i = l; i <= r; i++) {
     vec[i] = temp[i];
   }

   return inv_count;
 }


 int64_t insertionSort(std::vector<int>& vec, bool verbose = false) {
     int64_t inv_count{ 0 };
     int n = vec.size();
     std::vector<int> temp(n);

     for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
         for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
             int mid = std::min(left_start + curr_size - 1, n - 1);
             int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);

             inv_count += merge(vec, temp, left_start, mid, right_end);
         }
     }
     return inv_count; 
 }


  void check(vector<int> arr, int expected, bool verbose = false) {
    //auto result = insertionSortWithTree(arr, verbose);
    auto result = insertionSort(arr, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void main() {
  try {
    println("demo_QqqVova started ...\n");

    vector<int> arr = { 3, 2, 1 };

    check(arr, 3, true);


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }
}