//Time limit : 1.00 s
//Memory limit : 512 MB
//
//
//
//There are n applicants and m free apartments.Your task is to distribute the apartments so that as many applicants as possible will get an apartment.
//Each applicant has a desired apartment size, and they will accept any apartment whose size is close enough to the desired size.
//Input
//The first input line has three integers n, m, and k: the number of applicants, the number of apartments, and the maximum allowed difference.
//The next line contains n integers a_1, a_2, \ldots, a_n: the desired apartment size of each applicant.If the desired size of an applicant is x, he or she will accept any apartment whose size is between x - k and x + k.
//The last line contains m integers b_1, b_2, \ldots, b_m: the size of each apartment.
//Output
//Print one integer : the number of applicants who will get an apartment.
//Constraints
//
//1 \le n, m \le 2 \cdot 10 ^ 5
//0 \le k \le 10 ^ 9
//1 \le a_i, b_i \le 10 ^ 9
//
//Example
//Input :
//4 3 5
//60 45 80 60
//30 60 75
//
//Output :
//  2

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {
  class Apartments {
  public:

    Apartments(vector<int> persons, vector<int> flats, int k) : persons_{persons}, flats_{flats}, k_{k} {}


    int64_t findMaxPersons() {
      int64_t result{0};
      ranges::sort(persons_);
      ranges::sort(flats_);

      size_t size_pers = persons_.size();
      size_t size_flats = flats_.size();
      size_t startBackwardIdx = size_flats - 1;
      for (int64_t i = size_pers - 1; i >= 0; i--) {
        int64_t findResult = findBackwardFirstFlatIdx(i, startBackwardIdx);
        if (findResult != -1) {
          result++;
          if (startBackwardIdx > 0)
            startBackwardIdx--;
        }
      }
      return result;
    }


  private:

    int64_t findBackwardFirstFlatIdx(size_t personIdx, size_t startBackwardIdx) {
      int person = persons_[personIdx];
      for (int64_t i = startBackwardIdx; i >= 0; i--) {
        int flat = flats_[i];
        if (person >= flat - k_ && person <= flat + k_)
          return i;
      }
      return -1;
    }


    vector<int> persons_;
    vector<int> flats_;
    int k_;
  };



  void check(vector<int> persons, vector<int> flats, int k, int result) {
    Apartments aparts(persons, flats, k);
    if (aparts.findMaxPersons() != result) {
      println("Error with result = {}", result);
      throw exception("Error!");
    }
  }

}



void demo_Apartments() {
  //Apartments aparts({60, 45, 80, 60}, {30, 60, 75}, 5);
  //auto result = aparts.findMaxPersons();
  //println("result = {}", result);

  try {
    check({60, 45, 80, 60}, {30, 60, 75}, 5, 2);
    check({60, 45, 80, 60}, {30, 60, 75}, 50, 4);
    
    check({1, 2, 3, 4, 5}, {1, 2, 3}, 0, 3);
    check({1, 2, 3}, {1, 2, 3, 4, 5}, 0, 3);

    check({1, 2, 300, 4, 5}, {1, 2, 3}, 0, 2);
    check({1, 2, 300, 4, 5}, {1, 2, 3}, 1, 3);
    check({1, 2, 300, 4, 5}, {1, 2, 3, 4, 5}, 0, 4);


    println("All tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}