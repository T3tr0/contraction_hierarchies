#ifndef CSVPARSER_HH_
# define CSVPARSER_HH_

# include <iostream>
# include <vector>
# include "Road.hh"

using namespace std;

class CsvParser {
public:
  string path;
  vector<Road> roads;

  explicit CsvParser(string _path);
  CsvParser(CsvParser const &other);
  ~CsvParser();

  CsvParser	&operator=(CsvParser const &other);

  void Parse();

private:
  vector<string> splitCsvLine(string s);
};

vector<coordinate> addPoints(vector<string> &data);

#endif
