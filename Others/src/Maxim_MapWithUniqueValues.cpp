#include <print>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ranges>
//simple map with unuque values

#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  // https://stackoverflow.com/questions/36958502/how-to-avoid-duplicate-values-in-maps-using-c
  template<typename Key, typename T>
  class MapWithUniqueValues {
  public:
    bool isUnique() {
      return map_.size() == uniqueValues_.size();
    }

    void insert(Key key, T value) {
      map_.insert({key, value});
      uniqueValues_.insert(value);
    }
   
    //and many, many others ...

  private:
    unordered_map<Key, T> map_;
    set<T> uniqueValues_;
  };

}



void demo_Maxim_MapWithUniqueValues() {
  try {
    println("demo_Maxim_MapWithUniqueValues started ...\n");

    MapWithUniqueValues<string, int> map;
    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);
    println("isUnique = {}", map.isUnique());

    map.insert("qqq", 1);
    println("isUnique = {}", map.isUnique());

  } catch (exception ex) {
    println("{}", ex.what());
  }

}