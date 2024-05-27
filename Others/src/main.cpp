#include <print>
using namespace std;

void demo_Maxim_TwoStrings();
void demo_Maxim_MapWithUniqueValues();


int main() {
  try {
    demo_Maxim_TwoStrings();
    //demo_Maxim_MapWithUniqueValues();

  } catch (exception ex) {
    println("{}", ex.what());
  }
}
