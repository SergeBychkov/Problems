//In a movie festival n movies will be shown.You know the starting and ending time of each movie.What is the maximum number of movies you can watch entirely ?
//Input
//The first input line has an integer n : the number of movies.
//After this, there are n lines that describe the movies.Each line has two integers a and b : the starting and ending times of a movie.
//Output
//Print one integer : the maximum number of movies.
//Constraints
//
//1 \le n \le 2 \cdot 10 ^ 5
//1 \le a < b \le 10 ^ 9
//
//  Example
//  Input :
//3
//3 5
//4 9
//5 8
//
//Output :
//  2
#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include "random_utils.h"
using namespace std;

namespace {
  struct Movie {
    int start_;
    int finish_;
    bool deleted_{false};

    Movie(int start, int finish) : start_{start}, finish_{finish} {}
  };


  class MovieFestival {
  public:

    MovieFestival(vector<Movie> movies) : movies_{movies} {
      for (auto& mov : movies_) {
        if (mov.start_ >= mov.finish_)
          throw exception("Bad movie!");
      }
      moviesSortByFinish_ = movies;
      ranges::sort(movies_, [](Movie a, Movie b) {return a.start_ < b.start_; });
      ranges::sort(moviesSortByFinish_, [](Movie a, Movie b) {return a.finish_ < b.finish_; });
    }


    int work() {
      int result{};
      auto size = movies_.size();
      for (size_t i = 0; i < size; i++) {
        Movie& currMov = movies_[i];
        if (currMov.deleted_)
          continue;

        int testedIdx = i;
        while (testedIdx < size - 1) {
          testedIdx++;
          Movie& testedMov = movies_[testedIdx];
          if (testedMov.deleted_)
            continue;

          if (testedMov.start_ >= currMov.finish_)    //disjointed
            continue;
          if (testedMov.finish_ <= currMov.finish_) { //checkMov inside currMov
            currMov.deleted_ = true;
            break;
          } else {                                   //checkMov not inside currMov, but they are jointed  
            testedMov.deleted_ = true;
            continue;
          }
        }
        if (!currMov.deleted_)
          moviesChosen_.push_back(currMov);
      }
      checkMoviesChosen();
      return moviesChosen_.size();
    }



    int work_Vova() {  //much better!
      auto size = moviesSortByFinish_.size();
      int result{0};
      int cursor{0};
      for (size_t i = 0; i < size; i++) {
        if (moviesSortByFinish_[i].start_ >= cursor) {
          cursor = moviesSortByFinish_[i].finish_;
          result++;
        }
      }
      return result;
    }



    void printInitialMovies() {
      printMovies(movies_);
    }


    void printChosenMovies() {
      println("result = {}", moviesChosen_.size());
      printMovies(moviesChosen_);
    }


  private:
    void printMovies(vector<Movie> vec) {
      for (auto& movie : vec) {
        print("({}-{}), ", movie.start_, movie.finish_);
      }
      println("");
    }


    void checkMoviesChosen() {
      ranges::sort(moviesChosen_, [](Movie a, Movie b) {return a.start_ < b.start_; });
      for (size_t i = 0; i < moviesChosen_.size() - 1; i++) {
        if (moviesChosen_[i].finish_ > moviesChosen_[i + 1].start_)
          throw exception("Error in moviesChosen_!");
      }
    }


    vector<Movie> movies_, moviesSortByFinish_;
    vector<Movie> moviesChosen_;
  };



  void check(MovieFestival fest, int result) {
    if (fest.work() != result) {
      println("Error with result = {}", result);
      throw exception("Error!");
    }
    if (fest.work_Vova() != result) {
      println("Error with result = {}", result);
      throw exception("Error!");
    }
  }



  void autoCheck() {
    int n0 = 1'000;
    int nRand = 1'000;
    int nTests = 100;

    vector<Movie> movies0, movies;

    //long random movies, result = n0
    int duration0 = 1;
    int start = 0;
    for (size_t i = 0; i < n0; i++) {
      movies0.push_back(Movie(start, start + duration0));
      start += duration0;
    }
    movies = movies0;
    check(movies, n0);

    auto rndStart = Random::createRandomIntGenerator(0, (n0 - 1) * duration0); // all random  inside n0 * duration0!
    auto rndDuration = Random::createRandomIntGenerator(1, 10 * duration0);
    for (size_t i = 0; i < nTests; i++) {
      movies = movies0;
      for (size_t j = 0; j < nRand; j++) {
        int start = rndStart();
        int finish = start + rndDuration();
        movies.push_back(Movie(start, finish));
      }
      check(movies, n0);
    }


    //short random movies
    //n0 = 1000;
    n0 = 10;
    nRand = 1000;
    duration0 = 1000;
    movies0.clear();
    start = 0;
    for (size_t i = 0; i < n0; i++) {
      movies0.push_back(Movie(start, start + duration0));
      start += duration0;
    }
    rndStart = Random::createRandomIntGenerator(0, (n0 - 1) * duration0);
    rndDuration = Random::createRandomIntGenerator(1, 1);  //short movies!
    for (size_t i = 0; i < nTests; i++) {
      movies = movies0;
      for (size_t j = 0; j < nRand; j++) {
        int start = rndStart();
        int finish = start + rndDuration();
        movies.push_back(Movie(start, finish));
      }
      //check(movies, n0); //we dont' now exact result!
      MovieFestival fest(movies);
      auto result = fest.work();
      //fest.printChosenMovies(); break;
      println("result = {}", result);
    }

  }
}



void demo_MovieFestival() {
  MovieFestival fest(MovieFestival({{1, 10}, {2, 3}, {3, 10}}));
  fest.printInitialMovies();
  auto result = fest.work();
  fest.printChosenMovies();

  try {
    check(MovieFestival({{1, 2}}), 1);
    check(MovieFestival({{3, 4}, {1, 2}}), 2);
    check(MovieFestival({{1, 2}, {2, 3}}), 2);
    check(MovieFestival({{1, 10}, {1, 2}}), 1);
    check(MovieFestival({{1, 10}, {9, 10}}), 1);

    check(MovieFestival({{1, 10}, {1, 2}, {3, 4}}), 2);
    check(MovieFestival({{1, 10}, {9, 20}, {19, 30}}), 2);
    check(MovieFestival({{1, 10}, {2, 10}, {3, 10}}), 1);

    autoCheck();

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}