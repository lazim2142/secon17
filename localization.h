#include "ir_sensor.h"

// External references lead to secon17.ino
extern IRSensor ir_front_short, ir_front_long,
       ir_back_short, ir_back_long,
       ir_left_short, ir_left_long,
       ir_right_short, ir_right_long;

// Current Pose
extern float x, y;
extern int orientation;

namespace Localization
{

/*
This layer is the largest area, and	comprises over half
of the playing surface (45” wide by 57” long), and contains
the robot starting square and the locations of stages 1, 2 and 3.
The starting square is 15”x15” and is located in the center of
this space (15” from the inside of the long walls of the arena,
and	21” from the inside of the short wall).
*/

const float ARENA_LENGTH = 57;
const float ARENA_WIDTH = 45;
const float DIST_2_LONG_WALL = ARENA_LENGTH / 2;
const float DIST_2_SHORT_WALL = ARENA_WIDTH / 2;
const float ROBOT_RADIUS = 6;

// Gets the distance from the north, south, and east wall of the stage
// taking into account the current orientation of the robot to select the 
// appropriate sensors.
void getWallDistances(float& north_dist, float& south_dist, float& east_dist)
{
  switch (orientation)
  {
    case 0:
      north_dist = ir_left_long.getInches();
      if (north_dist < 12)
        north_dist = ir_left_short.getInches();
      south_dist = ir_right_long.getInches();
      if (south_dist < 12)
        south_dist = ir_right_short.getInches();
      east_dist = ir_front_long.getInches();
      if (east_dist < 12)
        east_dist = ir_front_short.getInches();
      break;

    case 90:
      north_dist = ir_front_long.getInches();
      if (north_dist < 12)
        north_dist = ir_front_short.getInches();
      south_dist = ir_back_long.getInches();
      if (south_dist < 12)
        south_dist = ir_back_short.getInches();
      east_dist = ir_right_long.getInches();
      if (east_dist < 12)
        east_dist = ir_right_short.getInches();
      break;

    case -90:
      north_dist = ir_back_long.getInches();
      if (north_dist < 12)
        north_dist = ir_back_short.getInches();
      south_dist = ir_front_long.getInches();
      if (south_dist < 12)
        south_dist = ir_front_short.getInches();
      east_dist = ir_left_long.getInches();
      if (east_dist < 12)
        east_dist = ir_left_short.getInches();
      break;

    case 180:
      north_dist = ir_right_long.getInches();
      if (north_dist < 12)
        north_dist = ir_right_short.getInches();
      south_dist = ir_left_long.getInches();
      if (south_dist < 12)
        south_dist = ir_left_short.getInches();
      east_dist = ir_back_long.getInches();
      if (east_dist < 12)
        east_dist = ir_back_short.getInches();
  }
}

// Origin is the center of the starting square
int north_south_switch_count = 0;
const int SWITCH_COUNT_MAX = 25;
void updatePose()
{
  float north_dist, south_dist, east_dist;
  getWallDistances(north_dist, south_dist, east_dist);

  x = DIST_2_LONG_WALL - east_dist;

  if (north_dist < south_dist)
    north_south_switch_count = min(SWITCH_COUNT_MAX, north_south_switch_count++);
  else
    north_south_switch_count = max(-SWITCH_COUNT_MAX, north_south_switch_count--);
    
  if (north_south_switch_count > 0)
    y = south_dist - DIST_2_SHORT_WALL;
  else
    y = DIST_2_SHORT_WALL - north_dist;
}
}
