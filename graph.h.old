// Graph class
// In this graph, nodes are integers in 0..num_nodes-1, and arcs are also
// integers in 0..num_arcs-1.
// Thus, when you AddArc(4, 128), you implicitly declare the existence of
// at least 129 nodes (0..128).
# include <vector>
# include <utility>
# include <iostream>

using namespace std;

typedef pair<int, int> arc;
typedef pair<double, double> coordinate;

class Graph {
private:
  vector<arc> arcs;
  vector<int> nodes;

public:
  int AddArc(int from, int to);    // Returns the arc index.

  // Optional: nodes are automatically added upon AddArc().
  void AddNode(int node);

  int NumNodes() const;
  int NumArcs() const;

  // Gets the tail ("from") and head ("to") of an arc.
  int Tail(int arc_index) const;
  int Head(int arc_index) const;

  // Returns a list of all the arc indices whose Tail is "from".
  const vector<int>& OutgoingArcs(int from) const;

  // Returns a list of all the arc indices whose Head is "to".
  const vector<int>& IncomingArcs(int to) const;
};
