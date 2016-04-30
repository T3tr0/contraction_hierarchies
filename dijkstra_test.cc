#include "base.h"
#include "graph.h"
#include "dijkstra.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
  Graph graph;
  vector<double> arc_lengths;
  graph.AddArc(4, 1); arc_lengths.push_back(3);
  graph.AddArc(0, 5); arc_lengths.push_back(0);
  graph.AddArc(1, 5); arc_lengths.push_back(1.2);
  graph.AddArc(3, 3); arc_lengths.push_back(0);
  graph.AddArc(3, 2); arc_lengths.push_back(0.4);
  graph.AddArc(2, 4); arc_lengths.push_back(2);
  graph.AddArc(2, 0); arc_lengths.push_back(1.5);
  graph.AddArc(5, 0); arc_lengths.push_back(0);
  graph.AddArc(1, 5); arc_lengths.push_back(1.1);
  graph.AddArc(3, 3); arc_lengths.push_back(1);
  graph.AddArc(4, 1); arc_lengths.push_back(1);
  graph.AddArc(1, 4); arc_lengths.push_back(0.5);
  graph.AddArc(1, 5); arc_lengths.push_back(1.3);
  graph.AddArc(4, 3); arc_lengths.push_back(0.1);

  Dijkstra dijkstra(&graph, &arc_lengths);
  // From '4'.
  dijkstra.Run(4);
  CHECK_EQ(PrintList(dijkstra.Distances()), "[ 2 1 0.5 0.1 0 2 ]");

  // From '0'
  dijkstra.Run(0);
  CHECK_EQ(PrintList(dijkstra.Distances()), "[ 0 inf inf inf inf 0 ]");

  // From '1'
  dijkstra.Run(1);
  CHECK_EQ(PrintList(dijkstra.Distances()), "[ 1.1 0 1 0.6 0.5 1.1 ]");

  // From '2'
  dijkstra.Run(2);
  CHECK_EQ(PrintList(dijkstra.Distances()), "[ 1.5 3 0 2.1 2 1.5 ]");

  // From '3'
  dijkstra.Run(3);
  CHECK_EQ(PrintList(dijkstra.Distances()), "[ 1.9 3.4 0.4 0 2.4 1.9 ]");

  // From '5'
  dijkstra.Run(5);
  CHECK_EQ(PrintList(dijkstra.Distances()), "[ 0 inf inf inf inf 0 ]");

  cout << "ALL TESTS PASSED!\n";
}
