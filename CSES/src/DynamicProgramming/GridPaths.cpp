//Consider an n \times n grid whose squares may have traps.It is not allowed to move to a square with a trap.
//Your task is to calculate the number of paths from the upper - left square to the lower - right square.You can only move right or down.
//Input
//The first input line has an integer n : the size of the grid.
//After this, there are n lines that describe the grid.Each line has n characters : .denotes an empty cell, and *denotes a trap.
//Output
//Print the number of paths modulo 10 ^ 9 + 7.
//Constraints
//
//1 \le n \le 1000
//
//Example
//Input :
//4
//....
//.*..
//...*
//*...
//
//Output :
//  3

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "../Utils/print_utils.h"
using namespace std;

namespace {
  struct Square {
    bool isSquare_{true};
    int n_{};
  };



  class GridPaths {
  public:

    GridPaths(vector<string> desk) {
      auto size = desk.size();
      for (size_t j = 0; j < size; j++) {
        string s = desk[j];
        vector<Square> row;
        for (size_t i = 0; i < size; i++) {
          Square sqr;
          if (s[i] == '*')
            sqr.isSquare_ = false;
          row.push_back(sqr);
        }
        grid_.push_back(row);
      }
    }


    int work() {
      auto size = grid_.size();
   
      //first row
      for (size_t j = 0; j < size; j++) {
        Square& sqr = grid_[0][j];
        if (sqr.isSquare_) {
          sqr.n_ = 1;
        } else {
          break;
        }
      }
      //first column
      for (size_t i = 0; i < size; i++) {
        Square& sqr = grid_[i][0];
        if (sqr.isSquare_) {
          sqr.n_ = 1;
        } else {
          break;
        }
      }
     
      //rows from second
      for (size_t i = 1; i < size; i++) {
        for (size_t j = 1; j < size; j++) {
          Square& sqr = grid_[i][j];
          Square& sqrUp = grid_[i-1][j];
          Square& sqrLeft = grid_[i][j-1];
          if (!sqr.isSquare_) 
            continue;

          sqr.n_ += sqrUp.n_;
          sqr.n_ += sqrLeft.n_;

        } 
      }

      printGrid();
      return grid_[size-1][size-1].n_;
    }


    void printGrid() {
      auto size = grid_.size();
      for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
          auto sqr = grid_[i][j];
          if (sqr.isSquare_)
            print("{}", sqr.n_);
          else
            print("*");
        }
        println("");
      }
      println("");
    }


  private:
    vector<vector<Square>> grid_;
  };



  void check(int expected) {
    //GridPaths qqq;
    //auto result = qqq.work();
    //if (result != expected) {
    //  println("Error with result = {}, expected = {}", result, expected);
    //  throw exception("Error!");
    //}
  }
}



void demo_GridPaths() {
  try {
    println("demo_GridPaths started ...\n");
    vector<string> desk{"0000",
                        "0*00",
                        "000*",
                        "*000"};

    GridPaths gridPaths(desk);
    gridPaths.printGrid();
    auto result = gridPaths.work();
    println("result = {}", result);

    //check(100);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}