//You have to process n tasks.Each task has a duration and a deadline, and you will process the tasks in some order one after another.Your reward for a task is d - f where d is its deadline and f is your finishing time. (The starting time is 0, and you have to process all tasks even if a task would yield negative reward.)
//What is your maximum reward if you act optimally ?
//Input
//The first input line has an integer n : the number of tasks.
//After this, there are n lines that describe the tasks.Each line has two integers a and d : the duration and deadline of the task.
//Output
//Print one integer : the maximum reward.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le a, d \le 10 ^ 6
//
//Example
//Input :
//3
//6 10
//8 15
//5 12
//
//Output :
//  2

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  struct Task {
    int duration_{};
    int deadline_{};
  };


  class TasksAndDeadlines {
  public:

    TasksAndDeadlines(vector<Task> tasks) : tasks_{tasks} {
      printTasks();
      ranges::sort(tasks_, [](Task a, Task b) {return a.duration_ < b.duration_; });
      printTasks();
    }


    int work() {
      int result{}, currStart{};
      for (auto& task : tasks_) {
        result += task.deadline_ - (currStart + task.duration_);
        currStart += task.duration_;
      }
      return result;
    }



    void printTasks() {
      for (auto& task : tasks_) {
        print("({} - {}), ", task.duration_, task.deadline_);
      }
      println("");
    }


  private:
    vector<Task> tasks_;
  };



  void check(int expected) {
    //TasksandDeadlines qqq;
    //auto result = qqq.work();
    //if (result != expected) {
    //  println("Error with result = {}, expected = {}", result, expected);
    //  throw exception("Error!");
    //}
  }
}



void demo_TasksandDeadlines() {
  try {
    println("demo_TasksAndDeadlines started ...\n");

    TasksAndDeadlines tasksAndDeadlines({{6, 10}, {8, 15}, {5, 12}});
    auto result = tasksAndDeadlines.work();
    println("result = {}", result);

    check(100);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}