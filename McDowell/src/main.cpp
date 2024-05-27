#include <print>
using namespace std;

//2_LinkedLists
void demo_Intersection();
void demo_8_LoopDetection();

//4_TreesAndGraphs
void demo_01_RouteBetweenNodes();


int main() {
  try {
    //2_LinkedLists
    //demo_Intersection();
    //demo_8_LoopDetection();

    //4_TreesAndGraphs
    demo_01_RouteBetweenNodes();


  } catch (exception ex) {
    println("{}", ex.what());
  }
}
