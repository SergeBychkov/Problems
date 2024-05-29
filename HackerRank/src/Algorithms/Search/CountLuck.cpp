//https://www.hackerrank.com/challenges/count-luck/problem?isFullScreen=true

#include <print>
#include <vector>
#include <deque>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {

  struct Field {
    bool free{};
    int steps{};
  };



  void printMatrix(vector<string> mat) {
    for (auto& row : mat) {
      println("{}", row);
    }
  }

  void printDesk(vector<vector<Field>>& desk) {
    for (auto& row : desk) {
      for (auto& field : row) {
        print("{:4}", field.steps);
      }
      println("");
    }
    println("");
  }


  string countLuck(vector<string> mat, int k, bool verbose = false) {
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<Field>> desk(m, vector<Field>(n));
    pair<int, int> start{}, finish{};
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        desk[i][j].free = mat[i][j] == '.' || mat[i][j] == '*';
        if (mat[i][j] == 'M') {
          start = {i, j};
          desk[i][j].steps = 1;
        }
        if (mat[i][j] == '*') {
          finish = {i, j};
        }
      }
    }

    auto processFields = [&](int i, int j, auto func) {
      if (i > 0)
        func(i - 1, j); //up
      if (i < m - 1)
        func(i + 1, j); //down
      if (j > 0)
        func(i, j - 1); //left
      if (j < n - 1)
        func(i, j + 1); //right
      };

    deque<pair<int, int>> stack;
    stack.push_front(start);
    int cnt = 0;
    while (!stack.empty()) {
      cnt++;
      auto currSquare = stack.back();
      stack.pop_back();
      int currSteps = desk[currSquare.first][currSquare.second].steps;

      if (currSquare == finish) {
        desk[currSquare.first][currSquare.second].steps = currSteps;
        break;
      }

      processFields(currSquare.first, currSquare.second, [&](int i, int j) {
        if (desk[i][j].free) {
          if (desk[i][j].steps == 0) {
            desk[i][j].steps = currSteps + 1;
            stack.push_front({i, j});
          }
        }
        }
      );
    }
    if (verbose) {
      printDesk(desk);
    }

    //move back 
    auto currSquare = finish;
    int currSteps = desk[finish.first][finish.second].steps;
    vector<pair<int, int>> path;
    while (currSteps != 1) {
      int tempSteps = currSteps;
      processFields(currSquare.first, currSquare.second, [&](int i, int j) {
        if (desk[i][j].steps == tempSteps - 1) {
          currSquare = {i, j};
          currSteps = desk[i][j].steps;
          path.push_back(currSquare);
        }
        }
      );
    }
    int result = 0;
    for (auto& field : path) {
      int choices = 0;
      processFields(field.first, field.second, [&](int i, int j) {
        int currSteps = desk[field.first][field.second].steps;
        if (desk[i][j].steps == currSteps + 1) {
          choices++;
        }
        }
      );
      if (choices > 1) {
        result++;
      }
    }
    return (result == k) ? "Impressed" : "Oops!";
  }



  void check(vector<string> mat, int k, string expected, bool verbose = false) {
    if (verbose)
      printMatrix(mat);
    auto result = countLuck(mat, k, verbose);
    if (result != expected) {
      println("Error with result = {}, expected = {}", result, expected);
      throw exception("Error!");
    }
  }
}



void demo_CountLuck() {
  try {
    println("demo_CountLuck started ...\n");

    vector<string> mat;

    //temp
    mat = {
      ".X.XXXXXXXXXXXXXXXXXXX.X.X.X.X.X.X.X.X.X.",
      "...XXXXXXXXXXXXXXXXXXX...................",
      ".X..X.X.X.X.X.X.X..XXXX*X.X.X.X.X.X.X.XX.",
      ".XXXX.X.X.X.X.X.X.XX.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.XX.X.XX.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.XXX.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      "X........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".X.XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.XX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XMX.",
      ".X....................................X..",
      "..X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".X...................................X...",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.XX.XXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      "........................................."
    };
    check(mat, 294, "Impressed", true);
    //return;


    mat = {
      "*.M",
      ".X."
    };
    check(mat, 1, "Impressed", true);

    mat = {
      ".X.X......X",
      ".X*.X.XXX.X",
      ".XX.X.XM...",
      "......XXXX."
    };
    check(mat, 3, "Impressed", true);

    mat = {
      ".X.X......X",
      ".X*.X.XXX.X",
      ".XX.X.XM...",
      "......XXXX."
    };
    check(mat, 4, "Oops!", true);


    //some site test
    mat = {
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      "M.......................................*",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X."
    };
    check(mat, 20, "Impressed", true);

    mat = {
      "..........*",
      ".XXXXXXXXXX",
      "...........",
      "XXXXXXXXXX.",
      "M.........."
    };
    check(mat, 0, "Impressed", true);

    mat = {
      "XXXXXXXXXXXXXXXXX",
      "XXX.XX.XXXXXXXXXX",
      "XX.*..M.XXXXXXXXX",
      "XXX.XX.XXXXXXXXXX",
      "XXXXXXXXXXXXXXXXX"
    };
    check(mat, 1, "Impressed", true);

    mat = {
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      "M........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".*......................................."
    };
    check(mat, 280, "Impressed", true);

    mat = {
      "XXXXXXXXXXXXXXXXX",
      "XXX.XX.XXXXXXXXXX",
      "XX.*..M.XXXXXXXXX",
      "XXX.XX.XXXXXXXXXX",
      "XXXXXXXXXXXXXXXXX"
    };
    check(mat, 280, "Oops!", true);


    mat = {
      ".X.XXXXXXXXXXXXXXXXXXX.X.X.X.X.X.X.X.X.X.",
      "...XXXXXXXXXXXXXXXXXXX...................",
      ".X..X.X.X.X.X.X.X..XXXX*X.X.X.X.X.X.X.XX.",
      ".XXXX.X.X.X.X.X.X.XX.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".XX.X.X.X.XX.X.XX.X.X.X.X.X.X.X.X.X.X.X.X",
      ".X.X.X.X.X.XXX.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      "X........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      ".X.XX.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.XX",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XMX.",
      ".X....................................X..",
      "..X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".X...................................X...",
      ".XX.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.XX.XXXX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      ".........................................",
      "X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX.",
      ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.",
      "........................................."
    };
    check(mat, 294, "Impressed", true);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}