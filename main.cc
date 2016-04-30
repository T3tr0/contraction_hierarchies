# include <iostream>
# include <cmath>
# include <utility>
# include <iomanip>
# include <map>
# include <list>

# include "csvparser.h"
# include "road.h"
# include "graph.h"

using namespace std;

typedef pair<int, int> arc;

double hav(double dif) {
  return (1 - cos(dif))/2;
}

double distance(std::pair<double, double>coord1, std::pair<double, double>coord2) {

  double r = 6371.0088;
  double pi = 3.14159265358979323846;

  double lat1 = coord1.first * pi / 180;
  double lng1 = coord1.second * pi / 180;

  double lat2 = coord2.first * pi / 180;
  double lng2 = coord2.second * pi / 180;

  double difLat = lat2 - lat1;
  double difLng = lng2 - lng1;

  double res = 2 * r * asin(
    sqrt(
      hav(difLat)
      + cos(lat1)
      * cos(lat2)
      * hav(difLng)
    )
  );

  return res * 1000;
}

map<coordinate, int> getNodes(vector<Road> &roads) {

  map<coordinate, int> node_list;
  int index = 0;

  vector<coordinate> all_coords;
  map<coordinate, int> coords_reccurence;

  for (vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it) {

    vector<coordinate> coordinates = (*it).coord_points;
    all_coords.insert(all_coords.end(), coordinates.begin(), coordinates.end());

    coordinate coord1 = make_pair(coordinates.front().first, coordinates.front().second);
    coordinate coord2 = make_pair(coordinates.back().first, coordinates.back().second);

    if (node_list.find(coord1) == node_list.end()) {
      node_list.insert(make_pair(coord1, index++));
    }

    if (node_list.find(coord2) == node_list.end()) {
      node_list.insert(make_pair(coord2, index++));
    }

  }

  for (vector<coordinate>::iterator it = all_coords.begin(); it != all_coords.end(); ++it) {
    pair<map<coordinate, int>::iterator, bool> res;

    res = coords_reccurence.insert(make_pair(*it, 1));
    if (!res.second)
    (*(res.first)).second++;
  }

  for (map<coordinate, int>::iterator it = coords_reccurence.begin(); it != coords_reccurence.end(); ++it) {
    if (it->second > 1)
    {
      node_list.insert(make_pair(it->first, index++));
    }
  }
  return node_list;
}

vector<arc> getArcs(map<coordinate, int> &nodes, vector<Road> &roads) {

  vector<arc> arcs;

  //   for (vector<Road>::iterator it_roads = roads.begin(); it_roads != roads.end(); ++it_roads) {
  //
  //     vector<coordinate> points = (*it_roads).coord_points;
  //     int i = 0;
  //
  //     while (i < (points.size() - 1)) {
  //       int j = i + 1;
  //       while (nodes.count(points[j]) == 0) j++;
  //       i = j;
  //       int index_node1 = nodes.find(points[i])->second;
  //       int index_node2 =  nodes.find(points[j])->second;
  //       arcs.push_back(make_pair(index_node1, index_node2));
  //       if (!(*it_roads).oneway)
  //       {
  //         arcs.push_back(make_pair(index_node2, index_node1));
  //       }
  //     }
  // }

  for (auto road: roads) {
    int i = 0;
    while (i < road.coord_points.size() - 1) {
      int j = i + 1;
      while (nodes.count(road.coord_points[j]) == 0) j++;
      int index_node1 = nodes.find(road.coord_points[i])->second;
      int index_node2 = nodes.find(road.coord_points[j])->second;
      arcs.push_back(make_pair(index_node1, index_node2));
      if (!road.oneway)
      arcs.push_back(make_pair(index_node2, index_node1));
      i = j;
    }
  }
  return arcs;
}

coordinate getCoordinate(std::map<coordinate, int> nodes, int numberOfNode) {
  for (auto node : nodes) {
    if (node.second == numberOfNode) {
      return node.first;
    }
  }
  return coordinate(-1, -1);
}

bool checkCoordinateWithRoad(coordinate firstCoordinate, coordinate secondCoordinate, Road road) {
  for (auto coordinateToFind : road.coord_points) {
    if (firstCoordinate == coordinateToFind) {
      for (auto secondCoordinateToFind : road.coord_points) {
        if (secondCoordinate == secondCoordinateToFind) {
          return true;
        }
      }
    }
  }
  return false;
}

double getDistance(coordinate firstCoordinate, coordinate secondCoordinate, Road road) {
  double distanceRoReturn = 0;

  std::vector<coordinate>::iterator it = road.coord_points.begin();
  for (; it != road.coord_points.end(); ++it) {
    if (firstCoordinate == (*it)) {
      while ((*it) != secondCoordinate) {
        distanceRoReturn += distance(*it, *(it));
        ++it;
      }
    }
  }
  return distanceRoReturn;
}

Road checkCoordinateWithRoads(coordinate firstCoordinate, coordinate secondCoordinate, std::vector<Road> roads) {
  for (auto road : roads) {
    if (checkCoordinateWithRoad(firstCoordinate, secondCoordinate, road)) {
      return road;
    }
  }
}

std::vector<double> getDistances(std::vector<Road> &roads, std::vector<arc> &arcs, std::map<coordinate, int> &nodes) {
  std::vector<double> distances;

  for (auto arc : arcs) {
    int firstNode = arc.first;
    int secondNode = arc.second;

    coordinate firstCoordinate = getCoordinate(nodes, firstNode);
    coordinate secondCoordinate = getCoordinate(nodes, secondNode);
    Road road = checkCoordinateWithRoads(firstCoordinate, secondCoordinate, roads);
    double distanceRoad = getDistance(firstCoordinate, secondCoordinate, road);
    distances.push_back(distanceRoad);
    // Get the exact road that are between the first and the second coordinate
    // Then get distance between one-to-one coordinate in a liste of double
    // then calcule divide by the limit speed
  }
  return distances;
}

void addArcs(Graph *graph, vector<arc> &arcs) {
  for (auto arc: arcs) {
    graph->AddArc(arc.first, arc.second);
  }
}

double fullDistance(vector<double> arc_lengths) {
  double full_dist = 0;

  for (auto length: arc_lengths) {
    full_dist += length;
  }
  return full_dist;
}

void usage() {
  cerr << "No file provided.\n[Usage: ./server file_path.csv]" << endl;
}

int main(int argc, char *argv[]) {

  map<coordinate, int> nodes;
  vector<arc> arcs;
  Graph graph;
  vector<double> arc_lengths;
  vector<Road> roads;

  if (argv[1] != NULL) {
    CsvParser parser = CsvParser(argv[1]);
    parser.Parse();
    roads = parser.roads;
    nodes = getNodes(roads);

    {
      cout << "### NODES ###" << endl;
      for (auto node: nodes) {
        coordinate coord = node.first;
        cout << "node[" << node.second << "]: " << coord.first << ", " << coord.second << endl;
      }
      cout << endl;
    }

    cout << nodes.size() << endl;
    arcs = getArcs(nodes, roads);

    {
      cout << "### ARCS ###" << endl;
      int i = 0;
      for (auto arc: arcs) {

        cout << "arc[" << i << "]: " << arc.first << ", "  << arc.second << endl;
        i++;
      }
      cout << endl;
    }

    cout << arcs.size() << endl;
    addArcs(&graph, arcs);
    arc_lengths = getDistances(roads, arcs, nodes);
    cout << arc_lengths[0] << endl;
    cout << fullDistance(arc_lengths) << endl;
  } else {
    usage();
  }

  return (0);
}
