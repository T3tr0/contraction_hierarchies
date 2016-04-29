# include "CsvParser.hh"
# include "Road.hh"
# include <map>
# include <list>

typedef pair<int, int> arc;

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
      cout << num_arcs << endl;
  return arcs;
}

void usage() {
  cerr << "No file provided.\n[Usage ./server file_path.csv]" << endl;
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
