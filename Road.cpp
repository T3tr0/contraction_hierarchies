#include "Road.hh"

Road::Road(string _name, enum e_priority _priority, int _max_speed, int _num_lanes, bool _oneway, int _numpoints, list<t_coordinates> _coord_points)
: name(_name), priority(_priority), max_speed(_max_speed), num_lanes(_num_lanes), oneway(_oneway), numpoints(_numpoints), coord_points(_coord_points) {}

Road::Road(Road const &other)
: name(other.name), priority(other.priority), max_speed(other.max_speed), num_lanes(other.num_lanes), oneway(other.oneway), numpoints(other.numpoints), coord_points(other.coord_points) {}

Road::~Road() {}

Road  &Road::operator=(Road const &other) {
  if (this != &other)
    {
      name = other.name;
      priority = other.priority;
      max_speed = other.max_speed;
      num_lanes = other.num_lanes;
      oneway = other.oneway;
      numpoints = other.numpoints;
      coord_points = other.coord_points;
    }
    return (*this);
}

ostream &operator<<(ostream &os, Road const &road) {
  os << "name : " << road.name << ", priority : " << road.priority
  << ", max_speed : " << road.max_speed << ", num_lanes : " << road.num_lanes
  << ", oneway : " << road.oneway << ", numpoints : " << road.numpoints << endl;
  os << "coord_points : ";
  for(list<t_coordinates>::const_iterator it = road.coord_points.begin(); it != road.coord_points.end(); ++it) {
    os << "[" << (*it).lat << ", " << (*it).lng <<"]" << endl;
  }
  return os;
}
