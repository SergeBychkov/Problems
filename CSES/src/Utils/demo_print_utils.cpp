#pragma once
#include <vector>
#include "print_utils.h"
using namespace std;

void demo_print_utils() {
  auto s = Print::formatStringWithWidth("qqq", 8);
  println("{}", s);
  println("{}", Print::formatStringWithWidth(123, 8));

  vector<int> vecLong{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Print::printVector(vecLong);
  Print::printVector(vecLong, 8, 0, 10);
  Print::printVector(vecLong, 8, 0, 5);
  Print::printVector(vecLong, 8, 5, 10);
  println("");

  vector<int> vecShort{1, 2, 3, 4, 5, 6};
  Print::printVector(vecShort);

  vector<double> vecDouble{{1.1, 2.22, 3.333, 4.444, 5, 6, 7, 8, 9}};
  Print::printVector(vecDouble, 16);
}
