//find a subarray with the length of a word from which this word can be composed

#include <print>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include <cstring>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  class Maxim_TwoStrings {
  public:

    Maxim_TwoStrings(string longString, string word) : longString_{longString}, word_{word} {}


    string work(bool verbose = false) {
      string result{};
      int wordSize = word_.size();
      int stringSize = longString_.size();
      unordered_set<char> wordSet(word_.begin(), word_.end());
      int wordHash = accumulate(word_.begin(), word_.end(), (int)0);
      int currHash = accumulate(longString_.begin(), longString_.begin() + wordSize, (int)0);
      int nProbes = 0;
      for (int i = 0; i <= stringSize - wordSize; i++) {
        if (i > 0) {
          currHash -= longString_[i - 1];
          currHash += longString_[i + wordSize - 1];
        }
        if (currHash == wordHash) {
          nProbes++;
          unordered_set<char> currSet(longString_.begin() + i, longString_.begin() + i + wordSize);
          if (currSet == wordSet) {
            result = string(longString_.begin() + i, longString_.begin() + i + wordSize);
            break;
          }
        }
      }
      if (verbose)
        println("nProbes = {}", nProbes);
      return result;
    }



    string work2(bool verbose = false) {
      string result{};
      int wordSize = word_.size();
      int stringSize = longString_.size();
      int wordHash = accumulate(word_.begin(), word_.end(), (int)0);
      int currHash = accumulate(longString_.begin(), longString_.begin() + wordSize, (int)0);

      int wordArr[128]{};
      int currArr[128]{};
      for (size_t i = 0; i < wordSize; i++) {
        wordArr[(int)word_[i]]++;
      }
      for (int i = 0; i <= stringSize - wordSize; i++) {
        if (i > 0) {
          currHash -= longString_[i - 1];
          currHash += longString_[i + wordSize - 1];
        }
        if (currHash == wordHash) {
          memset(currArr, 0, sizeof currArr);
          for (size_t j = i; j < i + wordSize; j++) {
            currArr[(int)longString_[j]]++;
          }
          if (memcmp(currArr, wordArr, sizeof currArr) == 0) {
            result = string(longString_.begin() + i, longString_.begin() + i + wordSize);
            break;
          }
        }
      }
      return result;
    }

  private:
    string longString_;
    string word_;
  };



  void check(string longString, string word, string expected) {
    Maxim_TwoStrings twoStrings(longString, word);
    auto result = twoStrings.work();
    auto result2 = twoStrings.work2();
    if (result != expected || result2 != expected) {
      println("Error with result = {}, result2 = {}, expected = {}", result, result2, expected);
      throw exception("Error!");
    }
  }



  void autoCheck() {
    int size = 1'000'000'000;
    //int size = 100'000'000;
    string longString;
    longString.resize(size);
    auto rnd = Random::createRandomIntGenerator(65, 122, true);
    for (size_t i = 0; i < size; i++) {
      longString[i] = (char)rnd();
    }
    longString[size - 1] = 'b';
    longString[size - 2] = 'e';
    longString[size - 3] = 'a';
    longString[size - 4] = 'r';
    longString[size - 5] = 'k';
    longString[size - 6] = 'i';
    longString[size - 7] = 's';
    longString[size - 8] = 'a';
    longString[size - 9] = 'b';
    longString[size - 10] = 'e';
    longString[size - 11] = 'a';
    longString[size - 12] = 'r';

    Maxim_TwoStrings twoStrings(longString, "kisabearbear");
    
    auto t1 = chrono::high_resolution_clock::now();
    auto result = twoStrings.work();
    auto t2 = chrono::high_resolution_clock::now();
    println("duration: {} sec", (double)(t2 - t1).count() / 1'000'000'000);
    println("result =  {}", result);

    t1 = chrono::high_resolution_clock::now();
    auto result2 = twoStrings.work2();
    t2 = chrono::high_resolution_clock::now();
    println("duration: {} sec", (double)(t2 - t1).count() / 1'000'000'000);
    println("result2 = {}", result2);
  }


}



void demo_Maxim_TwoStrings() {
  try {
    println("demo_Maxim_TwoStrings started ...\n");

    Maxim_TwoStrings twoStrings("QwertytacQuerty", "cat");
    auto result = twoStrings.work();
    println("result = {}", result);

    check("A", "A", "A");
    check("A", "B", "");
    check("QwertytacQuerty", "cat", "tac");
    check("abba", "ba", "ab");
    check("bc", "ab", "");

    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}