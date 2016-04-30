# include "dijkstra.h"

using namespace std;

Dijkstra::Dijkstra(const Graph* graph, const vector<double>* arc_lengths)
: graph_(*graph), arc_lengths_(*arc_lengths)
{
}

void Dijkstra::Run(int source) {
  DijkstraState s = {source , 0};
  parent_arc_.clear();
  distance_.clear();

  parent_arc_.resize(graph_.NumNodes(), -1);

  distance_.resize(graph_.NumNodes(), std::numeric_limits<double>::infinity());
  distance_[source] = 0;

  vector<int> out_arcs = graph_.OutgoingArcs(source);

  pq_.push(s);

  while (pq_.size() > 0) {
    DijkstraState p = pq_.top();
    pq_.pop();
    vector<int> tmp_arcs = graph_.OutgoingArcs(p.node);
    // cout << "***** arcs from source : " << tmp_arcs.size() << "*****" << endl << endl;
    for (auto arc: tmp_arcs) {
      // cout << "########" <<endl;
      // cout << "source: " << p.node << endl;
      // cout << "arc: " << arc << endl;
      // cout << "arc tail: " << graph_.Tail(arc) << endl;
      // cout << "arc head: " << graph_.Head(arc) << endl;
      // cout << "arc length: " << arc_lengths_[arc] << endl << endl;

      int arc_node_to = p.node == graph_.Head(arc) ? graph_.Tail(arc) : graph_.Head(arc);
      //  cout << "arc_node_to: " << arc_node_to << endl;
      //  cout << "arc_node_to distance: " << distance_[arc_node_to] << endl << endl;

      if (distance_[arc_node_to] ==  std::numeric_limits<double>::infinity()
      || distance_[arc_node_to] > p.distance + arc_lengths_[arc]) {
        // cout << "### update dist and parent ###" << endl;
        distance_[arc_node_to] = p.distance + arc_lengths_[arc];
        // cout << "arc_node_to distance: " << distance_[arc_node_to] << endl;
        parent_arc_[arc_node_to] = arc;
        // cout << "parent_arc:" << parent_arc_[arc_node_to] << endl;
        DijkstraState state = {arc_node_to, distance_[arc_node_to]};
        //cout << "new DijkstraState: " << state.node << ", " << state.distance << endl << endl;
        pq_.push(state);
      }
    }
  }
  cout << "###### ARC PATH #####" << endl;
  cout << "node source: " << source << endl;
  ArcPathFromSourceTo(5);
  cout << endl;
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
  cout << prev << " -> " ;
  while (arc != -1) {
    prev = (prev == graph_.Tail(arc)) ? graph_.Head(arc) : graph_.Tail(arc);
    res.push_back(arc);
    cout << prev << " -> " ;
    arc = parent_arc_[prev];
  }
  cout << "ARRIVED" << endl;
  return res;
}

/*
pop queue
take arcs
for all arcs
- update Distance & add to priority_queue if improvment
(update = distance of DijkstraState + distance to arc)
pop and repeat
*/
