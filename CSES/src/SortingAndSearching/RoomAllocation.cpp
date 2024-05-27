//There is a large hotel, and n customers will arrive soon.Each customer wants to have a single room.
//You know each customer's arrival and departure day. Two customers can stay in the same room if the departure day of the first customer is earlier than the arrival day of the second customer.
//What is the minimum number of rooms that are needed to accommodate all customers ? And how can the rooms be allocated ?
//Input
//The first input line contains an integer n : the number of customers.
//Then there are n lines, each of which describes one customer.Each line has two integers a and b : the arrival and departure day.
//Output
//Print first an integer k : the minimum number of rooms required.
//After that, print a line that contains the room number of each customer in the same order as in the input.The rooms are numbered 1, 2, \ldots, k.You can print any valid solution.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le a \le b \le 10 ^ 9
//
//Example
//Input :
//3
//1 2
//2 4
//4 4
//
//Output :
//  2
//  1 2 1

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "print_utils.h"
using namespace std;

namespace {
  struct Customer {
    int start_{};
    int finish_{};
    int roomIdx{};
  };


  struct Event {
    int time_{};
    bool isStart_{false};
    bool isFinish_{false};
    int custId_{};
  };


  struct TimePoint {
    int time_{};
    vector<Event> events_{};
  };


  class RoomAllocation {
  public:

    RoomAllocation(vector<Customer> customers) : customers_{customers} {
      for (size_t i = 0; i < customers_.size(); i++) {
        auto& cust = customers_[i];
        events_.emplace_back(cust.start_, true, false, i);
        events_.emplace_back(cust.finish_, false, true, i);
      }
      ranges::sort(events_, [](Event a, Event b) {return a.time_ < b.time_; });

      vector<int> times(events_.size());
      transform(events_.begin(), events_.end(), times.begin(), [](Event ev) {return ev.time_; });
      //print("times originals: "); Print::printVector(times);
      ranges::sort(times);
      auto last = std::unique(times.begin(), times.end());
      times.erase(last, times.end());
      //print("times uniques  : "); Print::printVector(times);

      int currEventIdx = 0;
      for (int time : times) {
        TimePoint tp{time};
        while (currEventIdx < events_.size() && events_[currEventIdx].time_ == time) {
          tp.events_.push_back(events_[currEventIdx]);
          currEventIdx++;
        }
        timePoints_.push_back(tp);
      }
    }



    int work(bool verbose = false) {
      int result{};
      int nIn{}, nOut{};
      for (const auto& timePoint : timePoints_) {
        for (const auto& event : timePoint.events_) {
          if (event.isStart_) {
            int roomIdx = getRoom();
            customers_[event.custId_].roomIdx = roomIdx;
          }
        }
        for (const auto& event : timePoint.events_) {
          if (event.isFinish_) {
            int custId = event.custId_;
            int roomIdx = customers_[custId].roomIdx;
            freeRoom(roomIdx);
          }
        }
      }

      if (verbose) {
        print("room: ");
        for (auto& cust : customers_) {
          print("{}, ", cust.roomIdx + 1); // rums numbering srarts with 1 in th problem
        }
        println("");
      }

      return rooms_.size();
    }



    void printInfo() {
      for (size_t i = 0; i < customers_.size(); i++) {
        print("({} - {}  [{}]), ", customers_[i].start_, customers_[i].finish_, i);
      }
      println("");
      for (const auto& event : events_) {
        print("({}, {}, {}, [{}]), ", event.time_, event.isStart_, event.isFinish_, event.custId_);
      }
      println("");
    }


  private:
    vector<Customer> customers_;
    vector<Event> events_;
    vector<TimePoint> timePoints_;
    vector<bool> rooms_;

    int getRoom() {
      int size = rooms_.size();
      for (size_t i = 0; i < size; i++) {
        if (!rooms_[i]) {
          rooms_[i] = true;
          return i;
        }
      }
      rooms_.push_back(true);
      return size;
    }


    void freeRoom(int roomIdx) {
      rooms_[roomIdx] = false;
    }
  };



  void check(vector<Customer> customers,  int expected) {
    RoomAllocation roomAllocation(customers);
    auto result = roomAllocation.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_RoomAllocation() {
  try {
    println("demo_RoomAllocation started ...");

    RoomAllocation roomAllocation({{1, 2}, {2, 4}, {4, 4}});
    roomAllocation.printInfo();
    auto result = roomAllocation.work(true);
    println("result = {}", result);

    check({{1, 2}, {2, 4}, {4, 4}}, 2);
    check({{1, 2}}, 1);
    check({{1, 2}, {2, 3}}, 2);
    check({{1, 2}, {2, 3}, {2, 4}}, 3);
    check({{1, 2}, {2, 3}, {3, 4}}, 2);
    check({{1, 2}, {2, 3}, {3, 4}, {4, 5}}, 2);
    check({{1, 3}, {3, 5}, {5, 7}, {2, 4}}, 3);


    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}