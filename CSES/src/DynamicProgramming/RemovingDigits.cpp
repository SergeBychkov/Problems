#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {

  class RemovingDigits {
  public:

    RemovingDigits(int num) : num_{num}, results_{vector<int>(num + 1)} {} // num+1 ! {}   


    int work() {
      results_[0] = 0;
      for (int x = 1; x <= num_; x++) {
        int result = 0;
        bool isFirstDigit = true;
        int temp = x;
        while (temp != 0) {
          int digit = temp % 10;
          temp /= 10;
          if (digit == 0)
            continue;

          int subResult = results_[x - digit];
          if (isFirstDigit) {
            result = subResult + 1;
            isFirstDigit = false;
          } else {
            result = min(result, subResult + 1);
          }
        }
        results_[x] = result;
      }
      return results_[num_];
    }



    int workVova() { //much easier and faster! 
      int result = 0;
      int x = num_;
      while (x > 0) {
        int temp = x;
        int maxDigit = 0;
        while (temp != 0) {
          int digit = temp % 10;
          temp /= 10;
          maxDigit = max(maxDigit, digit);
        }
        x -= maxDigit;  //substract max digit! 
        result++;
      }
      return result;
    }



    void printResults() {
      println("number  result");
      for (size_t i = 0; i < results_.size(); i++) {
        println("{:4}{:4} ", i, results_[i]);
      }
    }


  private:
    int num_;
    vector<int> results_;
  };


  void check() {
    for (size_t i = 1; i < 10'000; i++) {
      RemovingDigits solver(i);
      int result = solver.work();
      int resultVova = solver.workVova();
      if (result != resultVova) {
        println("Error with num = {}, result = {}", i, result);
        throw exception("Error!");
      }

    }
  }
}



void demo_RemovingDigits() {
  try {
    int result;
    //RemovingDigits solver(1'000'000);
    RemovingDigits solver(10000000);
    result = solver.work();
    //solver.printResults();
    println("result  = {}", result);
    result = solver.workVova();
    println("result2 = {}", result);

    check();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}