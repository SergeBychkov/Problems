#pragma once
#include <vector>
#include <random>
#include <functional>
using namespace std;

class Random {
public:
  static auto createRandomDoubleGenerator(double min = 0, double max = 1, bool newSeed = false) {
    std::random_device rd;   // Will be used to obtain a seed for the random number engine
    std::mt19937 gen0(0);
    std::mt19937 genRnd(rd());
    std::uniform_real_distribution<> distribution(min, max);
    if (newSeed)
      return std::bind(distribution, genRnd);  // Standard mersenne_twister_engine seeded with rd()
    else
      return std::bind(distribution, gen0);    // The same sequence!
  }



  static auto createRandomIntGenerator(int min = INT32_MIN, int max = INT32_MAX, bool newSeed = false) {
    std::random_device rd;   // Will be used to obtain a seed for the random number engine
    std::mt19937 gen0(0);
    std::mt19937 genRnd(rd());
    std::uniform_int_distribution<> distribution(min, max);
    if (newSeed)
      return std::bind(distribution, genRnd);  // Standard mersenne_twister_engine seeded with rd()
    else
      return std::bind(distribution, gen0);    // The same sequence!
  }



  static int* getRandomIntDynArray(size_t size, int min = INT32_MIN, int max = INT32_MAX, bool newSeed = false) {
    int* arr = new int[size];
    auto rnd = createRandomIntGenerator(min, max, newSeed);
    for (size_t i = 0; i < size; i++) {
      arr[i] = rnd();
    }
    return arr;
  }



  //static std::vector<int64_t> get_random_int64_vector(size_t size, int min = INT32_MIN, int max = INT32_MAX, bool newSeed = false) {
  static std::vector<int> getRandomIntVector(size_t size, int min = INT32_MIN, int max = INT32_MAX, bool newSeed = false) {
    std::vector<int> vec;
    vec.reserve(size);
    auto rnd = createRandomIntGenerator(min, max, newSeed);
    for (size_t i = 0; i < size; i++) {
      vec.push_back(rnd());
    }
    return vec;
  }
};



