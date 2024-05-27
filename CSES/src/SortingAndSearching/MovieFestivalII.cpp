//In a movie festival, n movies will be shown.Syrjälä's movie club consists of k members, who will be all attending the festival.
//You know the starting and ending time of each movie.What is the maximum total number of movies the club members can watch entirely if they act optimally ?
//Input
//The first input line has two integers n and k : the number of movies and club members.
//After this, there are n lines that describe the movies.Each line has two integers a and b : the starting and ending time of a movie.
//Output
//Print one integer : the maximum total number of movies.
//Constraints
//
//1 \le k \le n \le 2 \cdot 10 ^ 5
//1 \le a < b \le 10 ^ 9
//
//  Example
//  Input :
//5 2
//1 5
//8 10
//3 6
//2 5
//6 9
//
//Output:
//4

#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include "random_utils.h"
using namespace std;

namespace {
  struct Movie {
    int start_;
    int finish_;
    //bool deleted_{false};

    Movie(int start, int finish) : start_{start}, finish_{finish} {}
  };

  auto valueComparator = [](const Movie& a, const Movie& b) { return a.finish_ < b.finish_; };


  class MovieFestivalII {
  public:

    MovieFestivalII(vector<Movie> movies, int k) : movies_{movies}, k_{k} {
      for (auto& mov : movies_) {
        if (mov.start_ >= mov.finish_)
          throw exception("Bad movie!");
      }
      moviesSortByFinish_ = movies;
      ranges::sort(movies_, [](Movie a, Movie b) {return a.start_ < b.start_; });
      ranges::sort(moviesSortByFinish_, [](Movie a, Movie b) {return a.finish_ < b.finish_; }); //лишнее! 
    }



    int work() {
      int result{0};
      vector<vector<Movie>> members;
      multiset<Movie, decltype(valueComparator)> movies(moviesSortByFinish_.begin(), moviesSortByFinish_.end()); //can use movies_
      for (size_t i = 0; i < k_; i++) {
        vector<Movie> member;
        int cursor = 0;
        auto currIter = movies.begin();
        while (currIter != movies.end()) {
          auto curr = *currIter;
          if (curr.start_ >= cursor) {
            cursor = curr.finish_;
            currIter = movies.erase(currIter);
            result++;
            member.push_back(curr);
            continue;
          } else {
            currIter++;
          }
        }
        members.push_back(member);
      }
      return result;
    }



    void printInitialMovies() {
      printMovies(movies_);
    }


    //void printChosenMovies() {
    //  println("result = {}", moviesChosen_.size());
    //  printMovies(moviesChosen_);
    //}


  private:
    void printMovies(vector<Movie> vec) {
      for (auto& movie : vec) {
        print("({}-{}), ", movie.start_, movie.finish_);
      }
      println("");
    }


    //void checkMoviesChosen() {
    //  ranges::sort(moviesChosen_, [](Movie a, Movie b) {return a.start_ < b.start_; });
    //  for (size_t i = 0; i < moviesChosen_.size() - 1; i++) {
    //    if (moviesChosen_[i].finish_ > moviesChosen_[i + 1].start_)
    //      throw exception("Error in moviesChosen_!");
    //  }
    //}


    vector<Movie> movies_, moviesSortByFinish_;
    vector<Movie> moviesChosen_;
    int k_;
  };



  void check(vector<Movie> movies, int k,  int expected) {
    MovieFestivalII fest(movies, k);
    auto result = fest.work();
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_MovieFestivalII() {
  try {
    println("demo_MovieFestivalII started ...\n");

    vector<Movie> movies{{1,5}, {8, 10}, {3, 6}, {2, 5}, {6, 9}};
    int k = 2;
    MovieFestivalII fest(movies, k);
    fest.printInitialMovies();
    auto result = fest.work();
    println("result = {}", result);

    check({{1,5}, {8, 10}, {3, 6}, {2, 5}, {6, 9}}, 2, 4);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}