#include <iostream>
#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;


tuple<int, int> solve(vector<int>& vec) {
  int pos{}, sumDist{};
  ranges::sort(vec);
  auto size = vec.size();
  if(size == 0)
    throw exception("No germs!");

  int left = 0;
  int right = size - 1;
  while (true) {
    if (left == right) {
      pos = vec[left];
      break;
    } else if (left == right - 1) {
      pos = vec[left];
      sumDist += vec[right] - vec[left];
      break;
    } else {
      sumDist += vec[right] - vec[left];
      left++;
      right--;
    }
  }
  return {pos, sumDist};
}


void check(tuple<int, int> a, tuple<int, int> b) {
  if (a != b) 
    throw exception("Error!");
}


void printVector(const vector<int>& viruses) {
  for (const auto& v : viruses) {
    print("{} ", v);
  }
  println("");
}



int main() {
  vector<int> viruses;
  try {
  viruses = {10};
  check(solve(viruses), {10, 0});

  viruses = {0, 5};
  check(solve(viruses), {0, 5});
  viruses = {5, 0};
  check(solve(viruses), {0, 5});

  viruses = {1, 2, 3};
  check(solve(viruses), {2, 2});

  viruses = {0, 0, 5};
  check(solve(viruses), {0, 5});
  viruses = {0, 5, 5};
  check(solve(viruses), {5, 5});

  viruses = {0, 0, 0, 5};
  check(solve(viruses), {0, 5});
  viruses = {0, 5, 5, 5};
  check(solve(viruses), {5, 5});
  viruses = {0, 0, 5, 5};
  check(solve(viruses), {0, 10});

  viruses = {1, 2, 3, 4};
  check(solve(viruses), {2, 4});

  viruses = {1, 2, 1, 1, 4, 8, 4};
  auto [pos, sumDist] = solve(viruses);
  println("pos = {}, sumDist = {}", pos, sumDist);

  } catch (exception ex) {
    cout << ex.what() << "\n";
    printVector(viruses);
    return -1;
  }
  
  println("Tests passed!");
}