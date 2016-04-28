#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CsvParser.hh"

CsvParser::CsvParser(string _path) {
  path = _path;
}

CsvParser::CsvParser(CsvParser const &other) {
  path = other.path;
}

CsvParser::~CsvParser() {
}

CsvParser	&CsvParser::operator=(CsvParser const &other) {
  if (this != &other) {
    path = other.path;
    roads = other.roads;
  }
  return (*this);
}

void CsvParser::Parse() {
  ifstream data;
  string line;
  vector<string> v;

  data.open(path);
  if (data.is_open()) {
    while (getline(data, line)) {
      v = splitCsvLine(line);

      list<t_coordinates> points;

      vector<string>::iterator it = v.begin();
      advance(it, 6);
      for(; it != v.end(); ++it) {
        float lat = stof(*it);
        float lng = stof(*(++it));

        t_coordinates coords = {lat, lng};
        points.push_back(coords);
      }

      Road road = Road(v[0], t_priority(stoi(v[1])), stoi(v[2]), stoi(v[3]), stoi(v[4]), stoi(v[5]), points);
      roads.push_back(road);

      cout << road << endl;
    }

  } else {
    cout << "error open" << endl;
  }
}

vector<string> CsvParser::splitCsvLine(string s) {
  string str;
  istringstream is(s);
  vector<string> v;

  while (getline(is, str, ',')) {
    v.push_back(str);
  }
  return v;
}
