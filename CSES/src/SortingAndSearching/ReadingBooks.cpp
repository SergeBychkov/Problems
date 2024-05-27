// https://cses.fi/problemset/task/1631

// Time limit: 1.00 s
// Memory limit: 512 MB



// There are n books, and Kotivalo and Justiina are going to read them all. For each book, you know the time it takes to read it.
// They both read each book from beginning to end, and they cannot read a book at the same time. What is the minimum total time required?
// Input
// The first input line has an integer n: the number of books.
// The second line has n integers t_1,t_2,\dots,t_n: the time required to read each book.
// Output
// Print one integer: the minimum total time.
// Constraints

// 1 \le n \le 2 \cdot 10^5
// 1 \le t_i \le 10^9

// Example
// Input:
// 3
// 2 8 3

// Output:
// 16


#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

namespace {
  // ReadingBad - every reader takes free max length book every time ------------
  //bad at {4, 4, 1}, {2, 2, 2}, {2, 2, 2, 2, 2}

  class Book {
  public:
    int durationToRead{};
    bool isOccupied{false};
    bool readedBy_0{false};
    bool readedBy_1{false};
  };


  enum class ReaderStatus { Zero, Reading, Waiting, CompletedJob };

  class Reader {
  public:
    ReaderStatus status{ReaderStatus::Zero};
    int currBook{-1};
    int finishTimeForCurrBook{0};
    int nBooksFinished{0};
  };


  class ReadingBad {
  public:
    ReadingBad(vector<int> times) {
      ranges::sort(times, greater<int>());
      for (int i : times) {
        Book book;
        book.durationToRead = i;
        books_.push_back(book);
      }
      //printBooks();
    }



    int readBooks() {
      int count{};

      int currTime = 0;
      int nBooks = books_.size();
      while (true) {
        for (size_t i = 0; i < 2; i++) {
          Reader& reader = readers_[i];
          if (reader.status != ReaderStatus::CompletedJob && reader.status != ReaderStatus::Reading) {
            int bookIdx = findBookForReader(i);
            if (bookIdx != -1) {
              reader.status = ReaderStatus::Reading;
              reader.currBook = bookIdx;
              reader.finishTimeForCurrBook = currTime + books_[bookIdx].durationToRead;
            } else {
              reader.status = ReaderStatus::Waiting;
            }
          }
        }

        int finishTime_0 = readers_[0].finishTimeForCurrBook;
        int finishTime_1 = readers_[1].finishTimeForCurrBook;

        if (readers_[0].status == ReaderStatus::Reading && readers_[1].status == ReaderStatus::Reading) {
          if (finishTime_0 < finishTime_1) {
            currTime = finishTime_0;
            finishReadBook(0);
            readers_[0].status = ReaderStatus::Waiting;
          } else if (finishTime_0 > finishTime_1) {
            currTime = finishTime_1;
            finishReadBook(1);
            readers_[1].status = ReaderStatus::Waiting;
          } else {
            currTime = finishTime_0;
            finishReadBook(0);
            readers_[0].status = ReaderStatus::Waiting;
            finishReadBook(1);
            readers_[1].status = ReaderStatus::Waiting;
          }
        } else {
          if (readers_[0].status == ReaderStatus::Waiting || readers_[0].status == ReaderStatus::CompletedJob) {
            currTime = finishTime_1;
            finishReadBook(1);
            readers_[1].status = ReaderStatus::Waiting;
          } else if (readers_[1].status == ReaderStatus::Waiting || readers_[1].status == ReaderStatus::CompletedJob) {
            currTime = finishTime_0;
            finishReadBook(0);
            readers_[0].status = ReaderStatus::Waiting;
          }
        }

        for (auto& reader : readers_) {
          if (reader.nBooksFinished == nBooks)
            reader.status = ReaderStatus::CompletedJob;
        }
        if (readers_[0].status == ReaderStatus::CompletedJob && readers_[1].status == ReaderStatus::CompletedJob)
          break;
      }
      return currTime;
    }



    void printBooks() {
      for (auto book : books_) {
        println("{:2} {} {}", book.durationToRead, book.readedBy_0, book.readedBy_1);
      }
    }


  private:

    int findBookForReader(int nReader) {
      int result = -1;
      for (size_t i = 0; i < books_.size(); i++) {
        Book& book = books_[i];
        if (book.isOccupied)
          continue;
        else if (nReader == 0 && !book.readedBy_0) {
          book.isOccupied = true;
          return i;
        } else if (nReader == 1 && !book.readedBy_1) {
          book.isOccupied = true;
          return i;
        }
      }
      return -1; // not found
    }


    void finishReadBook(int nReader) {
      Reader& reader = readers_[nReader];
      reader.nBooksFinished++;
      books_[reader.currBook].isOccupied = false;
      if (nReader == 0) {
        books_[reader.currBook].readedBy_0 = true;
      } else {
        books_[reader.currBook].readedBy_1 = true;
      }
    }


    vector<Book> books_;
    vector<Reader> readers_{Reader(), Reader()};
  };



  //-----------------------------------------------------------------------------
  class Reading {
  public:
    Reading(vector<int> times) : times_{times} {}


    int readBooks() {
      int size = times_.size();
      if (size == 1) {
        return 2 * times_[0];
      } else if (size == 2) {
        int maximum = max<int>(times_[0], times_[1]);
        return 2 * maximum;
      }

      ranges::sort(times_, greater<int>());

      int time_middle = times_[size - 1];
      int t_even{}, t_odd{};
      for (size_t i = 0; i < times_.size() - 1; i++) {
        if (i % 2 == 0)
          t_even += times_[i];
        else
          t_odd += times_[i];
      }

      int time_max = max<int>(t_even, t_odd);
      int time_min = min<int>(t_even, t_odd);
      if (time_max > time_middle + time_min)       // (----8---) (-2) (-3-)
        return 2 * time_max;
      else if (time_max < time_middle + time_min)  // (----8---) (-2) (---7---)   - here time_max > time_min!
        return time_max + time_middle + time_min;
      else                                         // (----8---) (-2) (---6--)
        return 2 * time_max;
    }

  private:
    vector<int> times_;
  };



  void check(vector<int> times, int result) {
    Reading readind(times);
    if (readind.readBooks() != result) {
      println("Error with result = {}", result);
      throw exception("Error!");
    }
  }
}



void demo_ReadingBook() {
  try {
    check({2, 3, 8}, 16); //see comments in code
    check({2, 7, 8}, 17);
    check({2, 6, 8}, 16);

    check({2}, 4);
    check({2, 2}, 4);
    check({2, 3}, 6);

    check({2, 2, 2, 2}, 8);
    check({2, 2, 2, 2, 2, 2}, 12);
    check({2, 3, 2}, 7);

    check({2, 8, 3}, 16);
    check({2, 8, 6}, 16);
    check({2, 8, 7}, 17);

    //bad for ReadingBad:
    check({4, 4, 1}, 9);
    check({2, 2, 2}, 6);
    check({2, 2, 2, 2, 2}, 10);
    println("All tests passed!");


    //ReadingBad readind({2, 8, 3});
    //int result = readind.readBooks();
    //println("result = {}", result);
  } catch (exception ex) {
    println("{}", ex.what());
  }
}

