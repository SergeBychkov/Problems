//You are given a playlist of a radio station since its establishment.The playlist has a total of n songs.
//What is the longest sequence of successive songs where each song is unique ?
//Input
//The first input line contains an integer n : the number of songs.
//The next line has n integers k_1, k_2, \ldots, k_n: the id number of each song.
//Output
//Print the length of the longest sequence of unique songs.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le k_i \le 10 ^ 9
//
//Example
//Input :
//8
//1 2 1 3 2 7 4 2
//
//Output :
//  5
#include <print>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  class Playlist {
  public:

    Playlist(vector<int> songs) : songs_{songs} {}


    tuple<size_t, size_t>  work(bool verbose = false) {
      int idxMax1{}, idxMax2{};
      int idx1{}, idx2{};
      unordered_set<int> currSet;
      size_t size = songs_.size();
      while (idx2 < size) {
        int currSong = songs_[idx2];
        if (currSet.contains(currSong)) {
          //find the same and erase previous
          for (size_t i = idx1; i < idx2; i++) {
            currSet.erase(songs_[i]);
            if (currSong == songs_[i]) {
              idx1 = i + 1;
              break;
            }
          }
        }
        currSet.insert(currSong);

        if ((idx2 - idx1) > (idxMax2 - idxMax1)) {
          idxMax1 = idx1;
          idxMax2 = idx2;
        }
        if (verbose) {
          println("idx1 = {}, idx2 = {}", idx1, idx2);
          println("max1 = {}, max2 = {}", idxMax1, idxMax2);
          Print::printIterator(currSet.begin(), currSet.end());
          println("----------------------------------------------");
        }
        idx2++;
      }
      return {idxMax1, idxMax2};
    }


  private:
    vector<int> songs_;
  };



  void check(vector<int> vec, int expectedIdx1, int expectedIdx2) {
    Playlist playlist(vec);
    auto [idx1, idx2] = playlist.work();
    if (idx1 != expectedIdx1 && idx2 != expectedIdx2) {
      println("Error with result = ({}, {}), expected = ({}, {})", idx1, idx2, expectedIdx1, expectedIdx2);
      throw exception("Error!");
    }
  }
}



void demo_Playlist() {
  try {
    println("demo_Playlist started ...");

    vector<int> vec{1, 2, 1, 3, 2, 7, 4, 2};
    Playlist playlist(vec);
    auto [idx1, idx2] = playlist.work();
    Print::printVector(vec, 3);
    println("result = ({}, {})", idx1, idx2);
    Print::printVector(vec, 3, idx1, idx2 + 1);


    check({1}, 0, 0);
    check({1, 1}, 0, 0);
    check({1, 1, 2}, 1, 2);
    check({2, 1, 2}, 0, 1);
    check({1, 2, 3}, 0, 2);
    check({1, 2, 3, 1, 4}, 1, 4);
    check({1, 2, 3, 1, 4, 3}, 1, 4); 
    check({1, 1, 1, 2, 1}, 2, 3); 

    check({1, 2, 1, 3, 2, 7, 4, 2}, 2, 6);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}