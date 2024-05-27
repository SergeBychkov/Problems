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
  class Qqq {
  public:

    Qqq() {}


    int work() {
      int result{};

      return result;
    }


  private:

  };



  void check(int expected) {
    Qqq qqq;
    auto result = qqq.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_Qqq() {
  try {
    println("Qqq started ...\n");

    //Qqq qqq(100);
    //auto result = qqq.work();
    //println("result = {}", result);

    check(100);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}