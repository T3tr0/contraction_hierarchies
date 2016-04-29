# include "CsvParser.hh"
# include "Road.hh"
# include <map>
# include <list>

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

map<pair<int, int>, int> getArcs(map<coordinate, int> &nodes, vector<Road> &roads) {

  map<pair<int, int>, int> arcs;

  int To = -1;
  int From = -1;
  int index = 0;

  map<coordinate, int>::iterator res;

    for (vector<Road>::iterator it_roads = roads.begin(); it_roads != roads.end(); ++it_roads) {
      vector<coordinate> points = (*it_roads).coord_points;
      for (vector<coordinate>::iterator it_points = points.begin(); it_points != points.end(); ++it_points) {
        res = nodes.find(*it_points);
        if (res != nodes.end()) {
          if (From == -1) {
            From = res->second;
          } else {
            To = res->second;
            arcs.insert(make_pair(make_pair(From, To), index++));

            if (!(it_roads->oneway))
              arcs.insert(make_pair(make_pair(To, From), index++));

            it_points--;
            From = -1;
            To = -1;
          }
        }
      }
  }
  return arcs;
}

void usage() {
  cerr << "No file provided.\n[Usage ./server file_path.csv]" << endl;
}

int main(int argc, char *argv[]) {

  map<coordinate, int> nodes;
  map<pair<int, int>, int> arcs;

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
