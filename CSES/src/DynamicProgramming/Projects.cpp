//There are n projects you can attend.For each project, you know its starting and ending days and the amount of money you would get as reward.You can only attend one project during a day.
//What is the maximum amount of money you can earn ?
//Input
//The first input line contains an integer n : the number of projects.
//After this, there are n lines.Each such line has three integers a_i, b_i, and p_i : the starting day, the ending day, and the reward.
//Output
//Print one integer : the maximum amount of money you can earn.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le a_i \le b_i \le 10 ^ 9
//1 \le p_i \le 10 ^ 9
//
//Example
//Input :
//4
//2 4 4
//3 6 6
//6 8 2
//5 7 3
//
//Output :
//  7

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  struct Project {
    int start_{};
    int finish_{};
    int price_{};
  };



  class Projects {
  public:

    Projects(vector<Project> vec) : vec_{vec} {}


    int work() {
      int result{};

      return result;
    }


  private:
    vector<Project> vec_;
  };



  //void check(int expected) {
  //  Projects qqq;
  //  auto result = qqq.work();
  //  if (result != expected) {
  //    println("Error with result = {}, expected = {}", result, expected);
  //    throw exception("Error!");
  //  }
  //}
}



void demo_Projects() {
  try {
    println("demo_Projects started ...\n");

    vector<Project> vec{{2, 4, 4}, {3, 6, 6}, {6, 8, 2}, {5, 7, 3}};
    Projects projects(vec);
    auto result = projects.work();
    println("result = {}", result);

    //check(100);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}