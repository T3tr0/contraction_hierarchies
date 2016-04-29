#include "Graph.hh"

int Graph::AddArc(int from, int to) {
  arcs.push_back(make_pair(from, to));
  this.AddNode(from);
  this.AddNode(to);
  return arcs.size() - 1;
}

int Graph::AddNode(int node) {
  nodes.push_back(node);
}

int NumNodes() const {
  return nodes.size();
}

int NumArcs() const {
    return arcs.size();
}

int Graph::Tail(int arc) {
  arcs[arc].first;
}

int Graph::Head(int arc) {
  arcs[arc].second;
}

const vector<int>& OutgoingArcs(int from) {

  vector<int> res;
  int i = 0;

  while (i < arcs.size()) {
    if (arcs[i].first == from)
      res.push_back(i);
  }

  return res;
}

const vector<int>& IncomingArcs(int to) {

    vector<int> res;
    int i = 0;

    while (i < arcs.size()) {
      if (arcs[i].second == to)
        res.push_back(i);
    }

    return res;
}
