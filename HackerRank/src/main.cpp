#include <print>
using namespace std;

/// Algorithms/Search
void demo_CountLuck();
void demo_CutTheTree();
void demo_MinimumLoss();

/// Algorithms/Strings/
void demo_CommonChild();
void demo_SherlockAndTheValidString();

int main() {
  try {
    /// Algorithms/Search
    //demo_CountLuck();
    demo_CutTheTree();
    //demo_MinimumLoss();

    /// Algorithms/Strings/
    //demo_CommonChild();
    //demo_SherlockAndTheValidString();

  } catch (exception ex) {
    println("{}", ex.what());
  }
}

