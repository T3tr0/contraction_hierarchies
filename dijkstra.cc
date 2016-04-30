# include "dijkstra.h"

using namespace std;

Dijkstra::Dijkstra(const Graph* graph, const vector<double>* arc_lengths)
: graph_(*graph), arc_lengths_(*arc_lengths)
{
}

void Dijkstra::Run(int source) {
  parent_arc_.clear();
  distance_.clear();

  parent_arc_.resize(graph_.NumNodes(), -1);
  distance_.resize(graph_.NumNodes(), std::numeric_limits<double>::infinity());
  distance_[source] = 0;

  DijkstraState s = {source , 0};
  pq_.push(s);

  while (pq_.size() > 0) {
    DijkstraState p = pq_.top();
    pq_.pop();
    vector<int> tmp_arcs = graph_.OutgoingArcs(p.node);
    for (auto arc: tmp_arcs) {
      int arc_node_to = (p.node == graph_.Head(arc)) ? graph_.Tail(arc) : graph_.Head(arc);

      if (distance_[arc_node_to] ==  std::numeric_limits<double>::infinity()
      || distance_[arc_node_to] > p.distance + arc_lengths_[arc]) {

        distance_[arc_node_to] = p.distance + arc_lengths_[arc];
        parent_arc_[arc_node_to] = arc;

        DijkstraState state = {arc_node_to, distance_[arc_node_to]};

        pq_.push(state);
      }
    }
  }
}

const vector<double>& Dijkstra::Distances() const {
  return distance_;
}

const vector<int>& Dijkstra::ParentArcs() const {
  return parent_arc_;
}

vector<int> Dijkstra::ArcPathFromSourceTo(int node) const {
  vector<int> res;
  int arc = parent_arc_[node];
  int prev = node;

  while (arc != -1) {
    prev = (prev == graph_.Tail(arc)) ? graph_.Head(arc) : graph_.Tail(arc);
    res.push_back(arc);
    arc = parent_arc_[prev];
  }

  reverse(res.begin(), res.end());

  return res;
}
