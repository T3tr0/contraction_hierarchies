# include <iostream>
# include <cmath>
# include <utility>
# include <iomanip>
# include <map>
# include <list>
# include <cstdio>

//# include "csvparser.h"
// # include "road.h"
# include "graph.h"
# include "dijkstra.h"

using namespace std;

typedef pair<int, int> arc;

typedef pair<double, double> coordinate;

// map<coordinate, int> getNodes(vector<Road> &roads) {
//
//   map<coordinate, int> node_list;
//   int index = 0;
//
//   vector<coordinate> all_coords;
//   map<coordinate, int> coords_reccurence;
//
//   for (vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it) {
//
//     vector<coordinate> coordinates = (*it).coord_points;
//     all_coords.insert(all_coords.end(), coordinates.begin(), coordinates.end());
//
//     coordinate coord1 = make_pair(coordinates.front().first, coordinates.front().second);
//     coordinate coord2 = make_pair(coordinates.back().first, coordinates.back().second);
//
//     if (node_list.find(coord1) == node_list.end()) {
//       node_list.insert(make_pair(coord1, index++));
//     }
//
//     if (node_list.find(coord2) == node_list.end()) {
//       node_list.insert(make_pair(coord2, index++));
//     }
//
//   }
//
//   for (vector<coordinate>::iterator it = all_coords.begin(); it != all_coords.end(); ++it) {
//     pair<map<coordinate, int>::iterator, bool> res;
//
//     res = coords_reccurence.insert(make_pair(*it, 1));
//     if (!res.second)
//     (*(res.first)).second++;
//   }
//
//   for (map<coordinate, int>::iterator it = coords_reccurence.begin(); it != coords_reccurence.end(); ++it) {
//     if (it->second > 1)
//     {
//       node_list.insert(make_pair(it->first, index++));
//     }
//   }
//   return node_list;
// }
//
// vector<arc> getArcs(map<coordinate, int> &nodes, vector<Road> &roads, vector<double> *arc_lengths) {
//
//   vector<arc> arcs;
//   double distance = 0;
//
//   for (auto road: roads) {
//     int i = 0;
//     while (i < road.coord_points.size() - 1) {
//       int j = i + 1;
//       while (nodes.count(road.coord_points[j]) == 0) {
//         distance += calcDistance(road.coord_points[j -1], road.coord_points[j]);
//         j++;
//       }
//       distance += calcDistance(road.coord_points[j -1], road.coord_points[j]);
//       int index_node1 = nodes.find(road.coord_points[i])->second;
//       int index_node2 = nodes.find(road.coord_points[j])->second;
//       arcs.push_back(make_pair(index_node1, index_node2));
//       arc_lengths->push_back(distance / (road.max_speed * 1000) * 60 * 60);
//       if (!road.oneway) {
//         arcs.push_back(make_pair(index_node2, index_node1));
//         arc_lengths->push_back(distance / (road.max_speed * 1000) * 60 * 60);
//       }
//       distance = 0;
//       i = j;
//     }
//   }
//   return arcs;
// }
//
// void addArcs(Graph *graph, vector<arc> &arcs) {
//   for (auto arc: arcs) {
//     graph->AddArc(arc.first, arc.second);
//   }
// }
//
// double fullDistance(vector<double> arc_lengths) {
//   double full_dist = 0;
//
//   for (auto length: arc_lengths) {
//     full_dist += length;
//   }
//   return full_dist;
// }

void usage() {
  cerr << "No file provided.\n[Usage: ./server file_path.csv]" << endl;
}

int main(int argc, char *argv[]) {

  // map<coordinate, int> nodes;
  // vector<arc> arcs;
  // Graph graph;
  // vector<double> arc_lengths;
  //vector<Road> roads;
  RoadData roads;
  double lat1, lat2, lng1, lng2;
  string line;

  if (argv[1] != NULL) {
    roads = ParseCsvFile(argv[1]);
    // CsvParser parser = CsvParser(argv[1]);
    // parser.Parse();
    // roads = parser.roads;

    // nodes = getNodes(roads);
    // cout << nodes.size() << endl;

    // arcs = getArcs(nodes, roads, &arc_lengths);
    // cout << arcs.size() << endl;

    // addArcs(&graph, arcs);
    // double full_dist = fullDistance(arc_lengths);
    // printf("%lf\n", full_dist);

    // Dijkstra dijkstra(&graph, &arc_lengths);
    //
    // for (auto node: nodes) {
    //   static int i = 0;
    //   cout << "node[" << node.second << "]: " << node.first.first << "," << node.first.second << endl;
    //   if (i == 9)
    //     break;
    //   i++;
    // }

  //   while (getline(cin, line)) {
  //     if (sscanf(line.c_str(), "%lf,%lf->%lf,%lf", &lat1, &lng1, &lat2, &lng2) == 4) {
  //       coordinate coord1 = make_pair(lat1, lng1);
  //       coordinate coord2 = make_pair(lat2, lng2);
  //       auto node1 = nodes.find(coord1);
  //       auto node2 = nodes.find(coord2);
  //
  //       if (node1 == nodes.end() || node2 == nodes.end()) {
  //         cout << "INVALID\n";
  //         continue;
  //       }
  //       dijkstra.Run(node1->second);
  //       cout << "node[" << node1->second << "]: " << node1->first.first << ", " << node1->first.second << endl;
  //       cout << "node[" << node2->second << "]: " << node2->first.first << ", " << node2->first.second << endl;
  //       if (dijkstra.Distances()[node2->second] != std::numeric_limits<double>::infinity())
  //         cout << dijkstra.Distances()[node2->second];
  //       else {
  //         cout << "NO PATH" << endl;
  //         break;
  //       }
  //
  //       auto arc_path = dijkstra.ArcPathFromSourceTo(node2->second);
  //       for (auto arc : arc_path) {
  //         cout << " " << arc_lengths[arc];
  //       }
  //       cout << endl;
  //     }
  //     else
  //       cout << "INVALID\n";
  //   }
  // } else {
  //   usage();
  // }

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
        // cout << "node[" << node1->second << "]: " << node1->first.first << ", " << node1->first.second << endl;
        // cout << "node[" << node2->second << "]: " << node2->first.first << ", " << node2->first.second << endl;
        if (dijkstra.Distances()[node2->second] != std::numeric_limits<double>::infinity())
          cout << dijkstra.Distances()[node2->second];
        else {
          cout << "NO PATH" << endl;
          break;
        }

        // auto arc_path = dijkstra.ArcPathFromSourceTo(node2->second);
        // for (auto arc : arc_path) {
        //   cout << " " << roads.arc_durations[arc];
        // }
        // cout << endl;
      }
      else
        cout << "INVALID\n";
    }
  } else {
    usage();
  }

  return (0);
}
