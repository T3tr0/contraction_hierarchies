# include "dijkstra.h"

Dijkstra::Dijkstra(const *Graph graph, const vector<double>* arc_lengths)
: graph_(graph), arc_lengths_(arc_lengths)
{}

void Run(int source) {

}

const vector<double>& Distance() const {
  return distance_;
}

const vector<int>& ParentArcs() const {
  return parent_arc_;
}

vector<int> ArcPathFromSourceTo(int node) const {

}
