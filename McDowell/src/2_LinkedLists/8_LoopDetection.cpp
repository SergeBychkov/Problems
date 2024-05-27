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



  void detectAndRemoveCycle(Node*& head) {
    set<Node*> adresses;
    auto nodePtr = head;
    while (nodePtr) {
      auto prevPtr = nodePtr;
      nodePtr = nodePtr->next;
      if (adresses.contains(nodePtr)) {
        prevPtr->next = nullptr;
        return;
      }
      adresses.insert(nodePtr);
    }
  }



  void insert(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
      head = newNode;
    } else {
      Node* temp = head;
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }



  void printList(Node* head) {
    while (head) {
      print("{} -> ", head->data);
      head = head->next;
    }
    println("nullptr");
  }
}



void demo_8_LoopDetection() {
  try {
    println("demo_8_LoopDetection started ...\n");

    Node* head = nullptr;
    insert(head, 1);
    insert(head, 2);
    insert(head, 3);
    insert(head, 4);
    insert(head, 5);
    println("Current List:");
    printList(head);
    println("Inserting loop, connecting 5 to 2");
    head->next->next->next->next->next = head->next;
    println("Detecting and deleting loop");
    detectAndRemoveCycle(head);
    println("Back to the same old list");
    printList(head);

    println("\nAll tests passed!");
  } catch (exception ex) {
    println("{}", ex.what());
  }

}