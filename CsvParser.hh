#ifndef CSVPARSER_HH_
# define CSVPARSER_HH_

# include <iostream>
#include <vector>
# include <list>
# include "Road.hh"

using namespace std;

class CsvParser {
public:
  string path;
  list<Road> roads;

  explicit CsvParser(string _path);
  CsvParser(CsvParser const &other);
  ~CsvParser();

  CsvParser	&operator=(CsvParser const &other);

  void Parse();

private:
  vector<string> splitCsvLine(string s);
};

#endif
