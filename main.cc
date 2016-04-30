# include "csvparser.h"
# include "road.h"
# include <iostream>
# include <cmath>
# include <utility>
# include <iomanip>
# include <map>
# include <list>

typedef pair<int, int> arc;

float hav(float dif) {
        return (1 - cos(dif))/2;
}

float distance(std::pair<float, float>coord1, std::pair<float, float>coord2) {

        float r = 6371.0088;
        float pi = 3.14159265358979323846;

        float lat1 = coord1.first * pi / 180;
        float lng1 = coord1.second * pi / 180;

        float lat2 = coord2.first * pi / 180;
        float lng2 = coord2.second * pi / 180;

        float difLat = lat2 - lat1;
        float difLng = lng2 - lng1;

        float res = 2 * r * asin(
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

    for (vector<Road>::iterator it_roads = roads.begin(); it_roads != roads.end(); ++it_roads) {

      vector<coordinate> points = (*it_roads).coord_points;
      int max_speed = (*it_roads).max_speed;
      int i = 0;

      while (i < (points.size() - 1)) {
        int j = i + 1;
        while (nodes.count(points[j]) == 0) j++;
        i = j;
        int index_node1 = nodes.find(points[i])->second;
        int index_node2 =  nodes.find(points[j])->second;
        arcs.push_back(make_pair(index_node1, index_node2));
        if (!(*it_roads).oneway)
        {
          arcs.push_back(make_pair(index_node2, index_node1));
        }
      }
  }
  return arcs;
}

void usage() {
  cerr << "No file provided.\n[Usage ./server file_path.csv]" << endl;
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

float getDistance(coordinate firstCoordinate, coordinate secondCoordinate, Road road) {
  float distanceRoReturn = 0;

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

std::vector<float> getDistances(std::vector<Road> roads, std::vector<arc> arcs, std::map<coordinate, int> nodes) {
    std::vector<float> distances;

    for (auto arc : arcs) {
      int firstNode = arc.first;
      int secondNode = arc.second;

      coordinate firstCoordinate = getCoordinate(nodes, firstNode);
      coordinate secondCoordinate = getCoordinate(nodes, secondNode);
      Road road = checkCoordinateWithRoads(firstCoordinate, secondCoordinate, roads);
      float distanceRoad = getDistance(firstCoordinate, secondCoordinate, road);
      distances.push_back(distanceRoad);
      // Get the exact road that are between the first and the second coordinate
      // Then get distance between one-to-one coordinate in a liste of double
      // then calcule divide by the limit speed
    }
    return distances;
}

int main(int argc, char *argv[]) {

  map<coordinate, int> nodes;
  vector<arc> arcs;

  if (argv[1] != NULL) {
    CsvParser parser = CsvParser(argv[1]);
    parser.Parse();
    nodes = getNodes(parser.roads);
    cout << nodes.size() << endl;
    arcs = getArcs(nodes, parser.roads);
    cout << arcs.size() << endl;
  } else {
    usage();
  }

  return (0);
}
