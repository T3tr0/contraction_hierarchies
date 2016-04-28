// #ifndef GRAPH_HH
// #define  GRAPH_HH
//
// #include <vector>
//
// using namespace std;
//
// class Graph {
//  public:
//   int AddArc(int from, int to);  // Returns the arc index.
//
//   // Optional: nodes are automatically added upon AddArc().
//   void AddNode(int node);
//
//   // Gets the tail ("from") and head ("to") of an arc.
//   int Tail(int arc);
//   int Head(int arc);
//
//   // Returns a list of all the arc indices whose Tail is "from".
//   const vector& OutgoingArcs(int from) const;
//
//   // Returns a list of all the arc indices whose Head is "to".
//   const vector& IncomingArcs(int to) const;
//
//   // vector<int> ;
//
//   Graph();
//   ~Graph();
// };
//
// #endif
