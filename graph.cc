#include "graph.h"

int Graph::AddArc(int from, int to) {
  arcs.push_back(make_pair(from, to));
  this->AddNode(from);
  this->AddNode(to);
  return arcs.size() - 1;
}

void Graph::AddNode(int node) {
  nodes.push_back(node);
}

int Graph::NumNodes() const {
  int num = -1;
  for (auto node: nodes) {
    if (num < node)
      num = node;
  }
  return num + 1;
}

int Graph::NumArcs() const {
  return arcs.size();
}

int Graph::Tail(int arc_index) const {
  return this->arcs[arc_index].first;
}

int Graph::Head(int arc_index) const {
  return this->arcs[arc_index].second;
}

const vector<int>& Graph::OutgoingArcs(int from) const {

  vector<int> *res = new vector<int>;
  int i = 0;

  while (i < this->arcs.size()) {
    if (this->arcs[i].first == from)
      res->push_back(i);
    i++;
  }

  return *res;
}

const vector<int>& Graph::IncomingArcs(int to) const {

  vector<int> *res = new vector<int>;
  int i = 0;

  while (i < this->arcs.size()) {
    if (this->arcs[i].second == to)
      res->push_back(i);
    i++;
  }

  return *res;
}
