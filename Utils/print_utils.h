//https://stackoverflow.com/questions/75350469/is-stdformat-at-runtime-possible
//#include <iostream>
//#include <format>
//
//std::string centre(std::string string, int width, char fillchar = ' ') {
//  if (width <= string.size())
//    return string;
//  std::string fmt_str = std::format("|{{0:{}^{}}}|", fillchar, width);
//  return std::vformat(fmt_str, std::make_format_args(string));
//}
//
//int main() {
//  std::cout << centre("hello", 10, '*');
//}


#pragma once
#include <iostream>
#include <print>
#include <type_traits>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
//#include "common_utils.h"
using namespace std;


namespace Print {

  template<typename T>
  string formatStringWithWidth(T value, int width) {
    string fmt_str = std::format("{{:{}}}", width);
    return std::vformat(fmt_str, std::make_format_args(value));
  }


  //to save ?
  //template<typename... Args>
  //inline void printlnDyn(const std::format_string<Args...> fmt, Args&&... args) {
  //  std::cout << std::vformat(fmt.get(), std::make_format_args(args...)) << '\n';
  //}



  //to do
  //template<typename T>
  //inline string toString(const T& obj) {
  //  if constexpr (has_toString<T>)
  //    return format("{}", obj.toString());
  //  else
  //    return format("{}", obj);
  //}



  //template<typename T>
  //inline void write(const T& obj, int width = 6) {
  //  print("{:{}}", toString(obj), width);
  //}



  //template<typename T>
  //inline void writeLine(const T& obj) {
  //  print("{}\n", toString(obj));
  //}





  template<typename T>
  inline void printVector(const vector<T>& vec, int width = 8, size_t startIdx = 0, size_t endIdx = 0, bool printIndexes = false) {
    //old code
    //inline void printVector(const vector<T>& vec, int width = 8, int precision = 2) {
      //string sFormat = "{:{}}";
      ////if (std::is_same<T, double>::value) {
      ////  //sFormat = "{:{}." + to_string(precision) + "f}";
      ////  sFormat = "{:{}." + toString(precision) + "f}";
      ////}
    bool printAll;
    if (startIdx == 0 && endIdx == 0) {
      endIdx = vec.size();
      printAll = false;
    } else {
      printAll = true;
    }
    size_t size = endIdx - startIdx;

    if (size <= 8 || printAll) {
      for (size_t i = startIdx; i < endIdx; i++) {
        print("{}", formatStringWithWidth(vec[i], width));
      }
    } else {
      for (size_t i = startIdx; i < 4; i++) {
        print("{}", formatStringWithWidth(vec[i], width));
      }
      print(" . . . . . . . . . ");
      for (size_t i = endIdx - 4; i < endIdx; i++) {
        print("{}", formatStringWithWidth(vec[i], width));
      }
    }
    print("\n");

    if (printIndexes) {
      if (size <= 8 || printAll) {
        for (size_t i = startIdx; i < endIdx; i++) {
          print("{}", formatStringWithWidth(i, width));
        }
      } else {
        for (size_t i = startIdx; i < 4; i++) {
          print("{}", formatStringWithWidth(i, width));
        }
        print(" . . . . . . . . . ");
        for (size_t i = endIdx - 4; i < endIdx; i++) {
          print("{}", formatStringWithWidth(i, width));
        }
      }
      print(" - indexes\n");

    }
  }


  //to do
    //template<typename T>
    //inline void printVector(const vector<T>& vec, size_t from, size_t to, bool onNewLine = false, int width = 12) {
    //  size_t size = vec.size();
    //  if (from < 0 || from > size || to < 0 || to > size)
    //    throw out_of_range("invalid argument in printVector!");

    //  string sFormat = "{:{}}";
    //  if (onNewLine) {
    //    sFormat = "{:{}}\n";
    //  }
    //  if (std::is_same<T, double>::value) {
    //    sFormat = "{:{}.2f}";
    //    if (onNewLine) {
    //      sFormat = "{:{}}.2f\n";
    //    }
    //  }

    //  for (size_t i = from; i < to; i++) {
    //    print(sFormat, vec[i], width);
    //  }
    //}



  template<typename K, typename V>
  inline void printMap(map<K, V> map, int width = 8) { //to do
    for (const auto& item : map) {
      print("[{} → {}], ", item.first, item.second);
    }
    print("\n");
  }


  template<typename K, typename V>
  inline void printMap(unordered_map<K, V> map, int width = 8) { //to do
    for (const auto& item : map) {
      print("[{} → {}], ", item.first, item.second);
    }
    print("\n");
  }


  template<typename K, typename V>
  inline void printSet(multiset<K, V> map, int width = 8) { //to do
    for (const auto& item : map) {
      print("{}, ", item);
    }
    print("\n");
  }


  template<typename K, typename V>
  inline void printSet(unordered_multiset<K, V> map, int width = 8) { //to do
    for (const auto& item : map) {
      print("{}, ", item);
    }
    print("\n");
  }


  



  template<typename Iter>
  inline void printIterator(Iter begin, Iter end, int width = 8) {
    for (auto it = begin; it != end; ++it) {
      print("{}", formatStringWithWidth(*it, width));
    }
    print("\n");
  }


  //to do or delete? see above!
  //class PrintIter {
  //public:
  //  template<typename Iter>
  //  static void print(Iter it, Iter end, int width = 8) {
  //    string sFormat = "{:{}}";
  //    if (std::is_same<std::iterator_traits<Iter>::value_type, double>::value) {
  //      sFormat = "{:{}.2f}";
  //    }
  //    size_t count = 0;
  //    for (; it != end; ++it) {
  //      print(sFormat, *it, width);
  //      count++;
  //      if (count == 6)
  //        break;
  //    }
  //    print(". . . . \n");

  //  }
  //};

}
