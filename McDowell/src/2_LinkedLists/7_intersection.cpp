#include <print>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <chrono>
#include "print_utils.h"
#include "random_utils.h"
using namespace std;

namespace {
  struct Node {
    int data;
    Node* next;
    Node(int d) : data{d}, next{nullptr} {}
  };



  Node* intersectionPoint(Node* list1, Node* list2) {
    set<Node*> adresses;
    auto nodePtr = list1;
    while (nodePtr) {
      adresses.insert(nodePtr);
      nodePtr = nodePtr->next;
    }
    nodePtr = list2;
    while (nodePtr) {
      if (adresses.contains(nodePtr))
        return nodePtr;
      nodePtr = nodePtr->next;
    }
    return nullptr;
  }



  void printList(Node* head) {
    while (head) {
      print("{} -> ", head->data);
      head = head->next;
    }
    println("nullptr");
  }
}



void demo_Intersection() {
  try {
    println("demo_Intersection started ...\n");

    Node* list1 = new Node(3);
    list1->next = new Node(6);
    list1->next->next = new Node(9);
    list1->next->next->next = new Node(12);
    list1->next->next->next->next = new Node(15);
    list1->next->next->next->next->next = new Node(18);

    Node* list2 = new Node(7);
    list2->next = new Node(10);
    list2->next->next = list1->next->next->next;

    printList(list1);
    printList(list2);

    auto intersectingNode = intersectionPoint(list1, list2);
    if (intersectingNode) {
      println("Intersecting Node of lists is: {}", intersectingNode->data);
    } else {
      println("Lists do not interset");
    }

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}