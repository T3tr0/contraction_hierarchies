#ifndef ROAD_HH_
# define  ROAD_HH_

# include <iostream>
# include <list>

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

typedef struct s_coordinates {
  float lat;
  float lng;
} t_coordinates;

class Road {
public:
  string              name;
  t_priority     priority;
  int                 max_speed;
  int                 num_lanes;
  bool                oneway;
  int                 numpoints;
  list<t_coordinates> coord_points;

  explicit Road(string name, t_priority priority, int max_speed, int num_lanes, bool oneway, int numpoints, list<t_coordinates> coord_points);
  Road(Road const &other);
  ~Road();

  Road	&operator=(Road const &other);
};

ostream &operator<<(ostream &os, Road const &road);

#endif
