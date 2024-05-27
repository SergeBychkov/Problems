//A factory has n machines which can be used to make products.Your goal is to make a total of t products.
//For each machine, you know the number of seconds it needs to make a single product.The machines can work simultaneously, and you can freely decide their schedule.
//What is the shortest time needed to make t products ?
//Input
//The first input line has two integers n and t : the number of machines and products.
//The next line has n integers k_1, k_2, \dots, k_n: the time needed to make a product using each machine.
//Output
//Print one integer : the minimum time needed to make t products.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le t \le 10 ^ 9
//1 \le k_i \le 10 ^ 9
//
//Example
//Input :
//3 7
//3 2 5
//
//Output :
//  8
//
//  Explanation : Machine 1 makes two products, machine 2 makes four products and machine 3 makes one product.
#include <print>
#include <vector>
#include <queue>
#include <algorithm>
#include <ranges>
#include "random_utils.h"
#include "print_utils.h"
using namespace std;

namespace {
  struct Result {
    int64_t time_{};
    vector<int64_t> products_;
    vector<int64_t> times_;
  };



  class FactoryMachines {
  public:

    FactoryMachines(int nMach, int64_t kProd, vector<int> t) : nMach_{nMach}, kProd_{kProd}, t_{t} {
      ranges::sort(t_);
    }


    Result work(bool verbose = false) {
      vector<int64_t> products(nMach_), times(nMach_);
      int64_t maxTime = 0;

      double one_div_t = 0;
      for (size_t i = 0; i < nMach_; i++) {
        one_div_t += (1.0 / t_[i]);
      }
      double tAvr = kProd_ / one_div_t;

      int64_t productsSum = 0;
      for (size_t i = 0; i < nMach_; i++) {
        products[i] = (int64_t)tAvr / (int64_t)t_[i];
        times[i] = (int64_t)t_[i] * products[i];
        productsSum += products[i];
      }
      int64_t kProdMissing = kProd_ - productsSum;
      if (kProdMissing > nMach_)
        throw exception("kProdMissing > nMach_!");

      if (verbose) {
        println("tAvr = {:4.1f}, productsSum = {}, missing = {}", tAvr, productsSum, kProdMissing);
      }

      if (kProdMissing > 0) {
        vector<int64_t> timesTest(nMach_);
        for (size_t i = 0; i < nMach_; i++) {
          timesTest[i] = times[i] + t_[i];
        }
        ranges::sort(timesTest);
        maxTime = timesTest[kProdMissing - 1];
        //print("timesTest: "); Print::printVector(timesTest, 16);
      } else {
        maxTime = *ranges::max_element(times);
      }
      return Result(maxTime, products, times);
    }



    Result workByBinarySearch() {
      //https://usaco.guide/problems/cses-1620-factory-machines/solution
      int64_t lo = 0, hi = 1e18;
      int64_t maxTime = 0;
      while (lo <= hi) {
        int64_t mid = (lo + hi) / 2;
        int64_t sum = 0;
        for (int i = 0; i < nMach_; i++) {
          sum += (mid / t_[i]);
          if (sum >= kProd_) {  // deal with overflow
            break;
          }
        }
        if (sum >= kProd_) {
          maxTime = mid;
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      }
      vector<int64_t> products(nMach_), times(nMach_); //empty vectors 
      return Result(maxTime, products, times); 
    }



    void exactSolutionForCalculated_kProd() {
      vector<int64_t> products(nMach_), times(nMach_);
      int64_t kProd = 0;
      int64_t temp = 1;
      for (size_t i = 0; i < nMach_; i++) {
        temp *= t_[i];
      }
      for (size_t i = 0; i < nMach_; i++) {
        products[i] = temp / (int64_t)t_[i];
        times[i] = products[i] * t_[i];
        kProd += products[i];
      }
      println("Exact solution for calculated kProd:");
      println("kProd = {}", kProd);
      printResult(Result{*ranges::max_element(times), products, times});
    }



    void printResult(const Result& result) {
      print("nMach = {}, kProd = {}, t: ", nMach_, kProd_); Print::printVector(t_, 5, 0, t_.size());
      print("products: "); Print::printVector(result.products_, 15, 0, result.products_.size());
      print("times   : "); Print::printVector(result.times_, 15, 0, result.times_.size());
      println("result = {:16}", result.time_);
      println("");
    }



  private:
    int nMach_;
    int64_t kProd_;
    vector<int> t_;
  };



  Result checkWork(int nMach, int64_t kProd, vector<int> t, int64_t minTimeExpected) {
    FactoryMachines factoryMachines(nMach, kProd, t);
    auto result = factoryMachines.work();
    if (result.time_ != minTimeExpected) {
      println("Error in work() with time = {}, expected = {}", result.time_, minTimeExpected);
      print("nMach = {}, kProd = {}, t: ", nMach, kProd); Print::printVector(t, 5, 0, t.size());
      throw exception("Error!");
    }
    return result;
  }


  Result checkWorkByBinarySearch(int nMach, int64_t kProd, vector<int> t, int64_t minTimeExpected) {
    FactoryMachines factoryMachines(nMach, kProd, t);
    auto result = factoryMachines.workByBinarySearch();
    if (result.time_ != minTimeExpected) {
      println("Error in workByBinarySearch() with time = {}, expected = {}", result.time_, minTimeExpected);
      print("nMach = {}, kProd = {}, t: ", nMach, kProd); Print::printVector(t, 5, 0, t.size());
      throw exception("Error!");
    }
    return result;
  }


  void check(int nMach, int64_t kProd, vector<int> t, int64_t minTimeExpected) {
    checkWork(nMach, kProd, t, minTimeExpected);
    checkWorkByBinarySearch(nMach, kProd, t, minTimeExpected);
  }



  void autoTest() {
    //big numbers overflow int64_t!
    int nMach = 10;
    int nTests = 10;
    for (size_t i = 2; i <= nMach; i++) {
      for (size_t test = 0; test <= nTests; test++) {
        auto t = Random::getRandomIntVector(i, 2, 80, true);
        //auto t = Random::getRandomIntVector(i, 2, 80);
        int64_t kProd = 0;
        int64_t timeMin = 1;
        for (size_t j = 0; j < i; j++) {
          timeMin *= t[j];
        }
        for (size_t j = 0; j < i; j++) {
          kProd += timeMin / t[j];
        }
        //auto result = checkWork(i, kProd, t, timeMin);
        auto result = checkWorkByBinarySearch(i, kProd, t, timeMin);
        if (result.time_ != timeMin) {
          println("Error with maxTime = {}, expected = {}", result.time_, timeMin);
          print("nMach = {}, kProd = {}, timeMin = {}", i, kProd, timeMin); Print::printVector(t, 5, 0, t.size());
          throw exception("Error!");
        }
      }
    }
  }

}




void demo_FactoryMachines() {
  try {
    println("demo_FactoryMachines started ...");

    //int nMach = 3;
    //int64_t nProd = 31;
    //vector<int> t{2, 3, 5};

    int nMach = 6;
    int64_t nProd = 9514400640;
    vector<int> t{56, 60, 72, 85, 61, 86};

    FactoryMachines factoryMachines(nMach, nProd, t);
    auto result = factoryMachines.work(true);
    println("work():");
    factoryMachines.printResult(result);

    factoryMachines.exactSolutionForCalculated_kProd();

    check(3, 7, {3, 2, 5}, 8);
    check(3, 31, {2, 3, 5}, 30);

    autoTest();


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}