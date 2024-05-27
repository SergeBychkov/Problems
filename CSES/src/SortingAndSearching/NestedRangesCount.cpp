//Given n ranges, your task is to count for each range how many other ranges it contains and how many other ranges contain it.
//Range[a, b] contains range[c, d] if a \le c and d \le b.
//Input
//The first input line has an integer n : the number of ranges.
//After this, there are n lines that describe the ranges.Each line has two integers x and y : the range is[x, y].
//You may assume that no range appears more than once in the input.
//Output
//First print a line that describes for each range(in the input order) how many other ranges it contains.
//Then print a line that describes for each range(in the input order) how many other ranges contain it.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le x < y \le 10 ^ 9
//
//  Example
//  Input :
//4
//1 6
//2 4
//4 8
//3 6
//
//Output :
//  2 0 0 0
//  0 1 0 1

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  struct Range {
    int start_{};
    int finish_{};
    int id_{};
    int nIn_{0};
    int nOut_{0};
  };


  struct StartPoint {
    int x_{};
    int rangeId_{};
  };

  auto rangesComparator = [](const Range& a, const Range& b) { return a.finish_ < b.finish_; };
  auto pointsComparator = [](const StartPoint& a, const StartPoint& b) { return a.x_ < b.x_; };


  class NestedRangesCount {
  public:

    NestedRangesCount(vector<Range> ranges) : ranges_{ranges} {
      for (size_t i = 0; i < ranges_.size(); i++) {
        ranges_[i].id_ = i;
      }
      rangesSorted_.insert(ranges_.begin(), ranges_.end());
      for (const auto& range : ranges_) {
        StartPoint point(range.start_, range.id_);
        startPoints_.insert(point);
      }
    }



    tuple<vector<int>, vector<int>> work(bool verbose = false) {
      auto size = ranges_.size();
      if (size == 1)
        return {{0}, {0}};

      vector<int> resultIn(size), resultOut(size);
      int cursor{0};
      while (rangesSorted_.size() > 1) {
        auto firstIter = rangesSorted_.begin();
        auto firstRange = *firstIter;
        int firstId = firstRange.id_;
        int firstStart = firstRange.start_;
        int firstFinish = firstRange.finish_;

        auto savedPointIter = startPoints_.begin();

        for (auto currPointIter = startPoints_.begin(); currPointIter != startPoints_.end(); currPointIter++) {
          auto point = *currPointIter;
          if (point.x_ >= firstFinish)
            break;

          auto currId = point.rangeId_;
          auto currStart = ranges_[currId].start_;
          auto currFinish = ranges_[currId].finish_;

          if (verbose) {
            println("first : {} {} [{}]", firstStart, firstFinish, firstId);
            println("curr  : {} {} [{}]", currStart, currFinish, currId);
            printInfo();
            println("-------------------------------------------------------\n");
          }

          if (currStart < firstStart) {
            ranges_[firstId].nIn_++;
            ranges_[currId].nOut_++;
          } else if (currStart == firstStart) {
            if (currFinish == firstFinish) { //ranges are equals
              if (currId == firstId) {       //the same range, the code line will always be achieved!
                savedPointIter = currPointIter;
                continue;
              }
              ranges_[firstId].nIn_++;
              ranges_[firstId].nOut_++;
              ranges_[currId].nIn_++;
              ranges_[currId].nOut_++;
            } else if (currFinish > firstFinish) {
              ranges_[firstId].nIn_++;
              ranges_[currId].nOut_++;
            }
          } else if (currStart > firstStart) {
            if (currFinish == firstFinish) {
              ranges_[firstId].nOut_++;
              ranges_[currId].nIn_++;
            } else {
              //nothing to do
            }
          }
        }

        //detete first range and point
        rangesSorted_.erase(firstIter);
        startPoints_.erase(savedPointIter);
      }

      for (size_t i = 0; i < size; i++) {
          resultIn[i] = ranges_[i].nIn_;
          resultOut[i] = ranges_[i].nOut_;
      }
      return {resultOut, resultIn};
    }



    void printInit() {
      print("ranges init : ");
      for (auto item : ranges_) {
        print("({} - {} [{}]), ", item.start_, item.finish_, item.id_);
      }
      println("");
    }


    void printInfo() {
      print("rangesSorted: ");
      for (auto item : rangesSorted_) {
        print("({} - {} [{}]), ", item.start_, item.finish_, item.id_);
      }
      println("");
      print("points      : ");
      for (auto item : startPoints_) {
        print("{} [{}], ", item.x_, item.rangeId_);
      }
      println("");
    }


  private:

    vector<Range> ranges_;
    multiset<Range, decltype(rangesComparator)> rangesSorted_;
    multiset<StartPoint, decltype(pointsComparator)> startPoints_;
  };



  void check(vector<Range> ranges, vector<int> expectedOut, vector<int> expectedIn) {
    NestedRangesCount nestedRangesCount(ranges);
    auto [out, in] = nestedRangesCount.work();
    if (out != expectedOut && in != expectedIn) {
      println("Error with:");
      Print::printVector(out);
      Print::printVector(expectedOut);
      Print::printVector(in);
      Print::printVector(expectedIn);
      throw exception("Error!");
    }
  }
}



void demo_NestedRangesCount() {
  try {
    println("demo_NestedRangesCount started ...\n");

    vector<Range> vec{{1, 6}, {2, 4}, {4, 8}, {3, 6}};
    NestedRangesCount nestedRangesCount(vec);
    nestedRangesCount.printInit();
    nestedRangesCount.printInfo();
    auto [resultOut, resultIn] = nestedRangesCount.work();
    Print::printVector(resultOut, 3);
    Print::printVector(resultIn, 3);


    check({{1, 2}}, {0}, {0});
    check({{1, 2}, {1, 2}}, {1, 1}, {1, 1});
    check({{1, 2}, {1, 3}}, {0, 1}, {1, 0});
    check({{1, 2}, {2, 3}}, {0, 0}, {0, 0});
    check({{1, 2}, {2, 3}, {1, 4}}, {0, 0, 1}, {1, 1, 0});

    check({{1, 6}, {2, 4}, {4, 8}, {3, 6}}, {2, 0, 0, 0}, {0, 1, 0, 1});

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}