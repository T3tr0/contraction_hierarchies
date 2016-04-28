#include "CsvParser.hh"
#include "Road.hh"

// "/Users/ro22e0/Desktop/test.csv"

void usage() {
  cerr << "No file provided.\n[Usage ./server file_path.csv]" << endl;
}

int main(int argc, char *argv[]) {
  if (argv[1] != NULL)
  {
    CsvParser parser = CsvParser(argv[1]);
    parser.Parse();
  }
  else
    usage();
  return (0);
}
