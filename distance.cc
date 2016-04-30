# include <cmath>
# include <utility>
# include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

#include "base.h"

using std::cout;
using std::endl;

double hav(double dif) {
  return (1 - cos(dif))/2;
}

double calcDistance(std::pair<double, double>ll1, std::pair<double, double>ll2) {
  double lat1 = ll1.first;
  double lng1 = ll1.second;
  double lat2 = ll2.first;
  double lng2 = ll2.second;
  // Convert to radians...
  const double kDegToRad = 3.1415926535897932384626433 / 180;
  lat1 *= kDegToRad;
  lng1 *= kDegToRad;
  lat2 *= kDegToRad;
  lng2 *= kDegToRad;
  // https://en.wikipedia.org/wiki/Haversine_formula
  const double s1 = sin(0.5 * (lat2 - lat1));
  const double s2 = sin(0.5 * (lng2 - lng1));
  const double d = 2 * asin(sqrt(s1 * s1 + cos(lat1) * cos(lat2) * s2 * s2));
  // https://en.wikipedia.org/wiki/Earth_radius#Mean_radius
  const double kMeanEarthRadiusMeters = 6371008.8;
  return kMeanEarthRadiusMeters * d;
}
