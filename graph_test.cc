#include "base.h"
#include "graph.h"

#include <iostream>
using namespace std;

int main() {
  Graph graph;
  graph.AddNode(4);
  graph.AddNode(8);
  graph.AddNode(5);
  graph.AddNode(5);
  CHECK_EQ(graph.NumNodes(), 9);
  CHECK_EQ(graph.NumArcs(), 0);
  cout << "TEST PASSED: AddNode(), NumNodes(), NumArcs()." << endl;

  int a0 = graph.AddArc(1, 3);
  CHECK_EQ(graph.NumArcs(), 1);
  CHECK_EQ(a0, 0);

  int a1 = graph.AddArc(1, 3);
  CHECK_EQ(graph.NumArcs(), 2);
  CHECK_EQ(a1, 1);

  int a2 = graph.AddArc(3, 1);
  CHECK_EQ(a2, 2);
  CHECK_EQ(graph.NumArcs(), 3);

  graph.AddArc(5, 5);
  graph.AddArc(5, 0);
  graph.AddArc(10, 1);
  CHECK_EQ(graph.NumArcs(), 6);
  cout << "TEST PASSED: AddArc() and NumArcs()." << endl;

  CHECK_EQ(graph.NumNodes(), 11);  // We implicitly created nodes 0..10.
  cout << "TEST PASSED: AddArc() adds nodes." << endl;

  // Check arc #2 (a2), i.e. 3->1
  CHECK_EQ(graph.Tail(2), 3);
  CHECK_EQ(graph.Head(2), 1);
  cout << "TEST PASSED: Tail() and Head()." << endl;

  // CHECK adjacency lists.
  CHECK_EQ(PrintList(graph.OutgoingArcs(1)), "[ 0 1 ]");
  CHECK_EQ(PrintList(graph.IncomingArcs(1)), "[ 2 5 ]");
  CHECK_EQ(PrintList(graph.OutgoingArcs(5)), "[ 3 4 ]");
  CHECK_EQ(PrintList(graph.IncomingArcs(5)), "[ 3 ]");
  CHECK_EQ(PrintList(graph.IncomingArcs(9)), "[ ]");

  cout << "TEST PASSED: OutgoingArcs(), IncomingArcs()." << endl;

  cout << "ALL TESTS PASSED! Bravo!\n";
}
