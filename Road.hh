#ifndef ROAD_HH_
# define  ROAD_HH_

# include <iostream>
# include <vector>

using namespace std;

typedef enum e_priority {
  NATIONAL_HIGHWAY = 0,
  HIGHTWAY,
  REGIONAL,
  INTER_COMMUNAL,
  LOCAL_ROAD,
  TWO_WAY,
  PRIVATE
} t_priority;

typedef pair<float, float> coordinate;

class Road {
public:
  string name;
  t_priority priority;
  int max_speed;
  int num_lanes;
  bool oneway;
  int numpoints;
  vector<coordinate> coord_points;

  Road(string name, t_priority priority, int max_speed, int num_lanes, bool oneway, int numpoints, vector<coordinate> coord_points);
  Road(Road const &other);
  ~Road();

  Road  &operator=(Road const &other);
};

ostream &operator<<(ostream &os, Road const &road);

#endif
