#include "CsvParser.hh"
#include "Road.hh"
#include <map>
#include <list>

// "/Users/ro22e0/Desktop/test.csv"

map<pair<float, float>, int> getRedPoint(list<Road> roads) {
  map<pair<float, float>, int> redPointsList;
  list<Road>::iterator it = roads.begin();

  for(; it != roads.end(); ++it) {
    list<t_coordinates> coordinates = (*it).coord_points;
    t_coordinates firstCoordinate =
              {coordinates.front().lat, coordinates.front().lng};
    t_coordinates lastCoordinate =
              {coordinates.back().lat, coordinates.back().lng};
    redPointsList.insert(pair<pair<float, float>, int>(pair<float, float>(
      firstCoordinate.lat, firstCoordinate.lng), redPointsList.size()));
    redPointsList.insert(pair<pair<float, float>, int>(pair<float, float>(
      lastCoordinate.lat, lastCoordinate.lng), redPointsList.size()));
  }

  // map<pair<float, float>, int>::const_iterator it2 = redPointsList.begin();
  // for(; it2 != redPointsList.end(); ++it2) {
    // cout << it2->second << " || { "
      // << (it2->first).first << " , " << (it2->first).second << " }" <<endl;
  // }
  cout << redPointsList.size() << endl;
  return redPointsList;
}

void getIntersection(list<Road> roads) {

}

void usage() {
  cerr << "No file provided.\n[Usage ./server file_path.csv]" << endl;
}

int main(int argc, char *argv[]) {
  if (argv[1] != NULL)
  {
    CsvParser parser = CsvParser(argv[1]);
    parser.Parse();
    getRedPoint(parser.roads);
  }
  else
    usage();
  return (0);
}
