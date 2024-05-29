#include <print>
using namespace std;

/// Algorithms/Search
void demo_CountLuck();
 
/// Algorithms/Strings/
void demo_CommonChild();
void demo_SherlockAndTheValidString();

int main() {
  try {
    /// Algorithms/Search
    demo_CountLuck();

    /// Algorithms/Strings/
    //demo_CommonChild();
    //demo_SherlockAndTheValidString();

  } catch (exception ex) {
    println("{}", ex.what());
  }
}

