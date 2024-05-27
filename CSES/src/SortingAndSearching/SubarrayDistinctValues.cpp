//Given an array of n integers, your task is to calculate the number of subarrays that have at most k distinct values.
//Input
//The first input line has two integers n and k.
//The next line has n integers x_1, x_2, \dots, x_n: the contents of the array.
//Output
//Print one integer : the number of subarrays.
//Constraints
//
//1 \le k \le n \le 2 \cdot 10 ^ 5
//1 \le x_i \le 10 ^ 9
//
//Example
//Input :
//5 2
//1 2 3 1 1
//
//Output :
//  10

#include <print>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  class SubarrayDistinctValues {
  public:

    SubarrayDistinctValues(vector<int> vec, int k) : vec_{vec}, k_{k} {}


    int work(bool verbose = false) {
      int result{};
      int idx1 = 0, idx2 = 1;
      map<int, int> map;
      map[vec_[0]] = 1;
      size_t size = vec_.size();
      while (true) {
        //if (verbose) {
        //  println("idx1 = {}, idx2 = {}, result = {}", idx1, idx2, result);
        //}
        map[vec_[idx2]]++;
        if (!isRightSubArray(map)) {
          while (!isRightSubArray(map)) {
            if (idx2 - idx1 > 1) {
              map[idx1]--;
              if (map[idx1] == 0)
                map.erase(map[idx1]);
              result += idx2 - idx1;
              idx1++;
            } else {
              result += 1;
              idx1++;
              break;
            }
          }
        }
        if (idx2 == size - 1)
          break;
        idx2++;
      }
      if (isRightSubArray(map)) {      // 1 1 1 1 1 1  //idx2 = size-1, idx1 < size-1   //k_ = 1
        int len = idx2 - idx1 + 1;
        result += (len + 1) * len / 2;
      } else {                         // 1 1 1 1 1 2  //idx2 = size-1, idx1 = size-2   //k_ = 1
        result += 1;
        //result += 2;
      }
      return result;
    }


  private:
    bool isRightSubArray(map<int, int> map) {
      return (map.size() <= k_) ? true : false;
    }

    vector<int> vec_;
    int k_;
  };



  void check(vector<int> vec, int k, int expected) {
    SubarrayDistinctValues subarrayDistinctValues(vec, k);
    auto result = subarrayDistinctValues.work();
    if (result != expected) {
      print("k = {}, vec: ", k); Print::printVector(vec, 3);
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }



  void demoHelper(vector<int> vec, int k) {
    SubarrayDistinctValues subarrayDistinctValues(vec, k);
    auto result = subarrayDistinctValues.work(false);
    print("k = {}, vec: ", k); Print::printVector(vec, 3);
    println("result = {}\n\n", result);
  }
}



void demo_SubarrayDistinctValues() {
  try {
    println("demo_SubarrayDistinctValues started ...\n");
    //vector<int> vec{1, 1};
    //int k = 2;
    //SubarrayDistinctValues subarrayDistinctValues(vec, k);
    //auto result = subarrayDistinctValues.work();
    //print("k = {}, ", k); Print::printVector(vec, 3);
    //println("result = {}", result);
    
    demoHelper({0, 1, 2, 3}, 2);

    check({1, 1}, 1, 3);
    check({1, 1, 1}, 1, 6);
    check({1, 1, 1, 1}, 1, 10);
    
    check({1, 1}, 2, 3);
    check({1, 1, 1}, 2, 6);
    check({1, 1, 1, 1}, 2, 10);

    check({0, 1}, 1, 2);
    check({0, 1, 2}, 1, 3);
    check({0, 1, 2, 4}, 1, 4);

    check({0, 1}, 2, 3);
    check({0, 1, 2}, 2, 5);
    check({0, 1, 2, 3}, 2, 7);



    //check({0, 1}, 1, 2);
    //check({1, 1}, 1, 3);
    //check({0, 1}, 2, 3);
    //check({1, 1}, 2, 3);

    //check({0, 1, 2}, 1, 3);
    //check({0, 1, 2}, 2, 5); //bad

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}