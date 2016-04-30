# include <iostream>
# include <cmath>
# include <utility>
# include <iomanip>
# include <map>
# include <list>
# include <cstdio>
# include "graph.h"
# include "dijkstra.h"

using namespace std;

typedef pair<int, int> arc;

typedef pair<double, double> coordinate;

void usage() {
  cerr << "No file provided.\n[Usage: ./server file_path.csv]" << endl;
}

int main(int argc, char *argv[]) {

  RoadData roads;
  double lat1, lat2, lng1, lng2;
  string line;

  if (argv[1] != NULL) {
    roads = ParseCsvFile(argv[1]);

  Dijkstra dijkstra(&(roads.graph), &(roads.arc_durations));
    while (getline(cin, line)) {
      if (sscanf(line.c_str(), "%lf,%lf->%lf,%lf", &lat1, &lng1, &lat2, &lng2) == 4) {
        coordinate coord1 = make_pair(lat1, lng1);
        coordinate coord2 = make_pair(lat2, lng2);
        auto node1 = roads.latlng_to_node.find(coord1);
        auto node2 = roads.latlng_to_node.find(coord2);

        if (node1 == roads.latlng_to_node.end() || node2 == roads.latlng_to_node.end()) {
          cout << "INVALID\n";
          continue;
        }
        dijkstra.Run(node1->second);

        if (dijkstra.Distances()[node2->second] != std::numeric_limits<double>::infinity())
          cout << dijkstra.Distances()[node2->second];
        else {
          cout << "NO PATH" << endl;
          break;
        }

        auto arc_path = dijkstra.ArcPathFromSourceTo(node2->second);
        for (auto arc : arc_path) {
          cout << " " << roads.arc_durations[arc];
        }
        cout << endl;
      }
      else
        cout << "INVALID\n";
    }
  } else {
    usage();
  }

  return (0);
}
