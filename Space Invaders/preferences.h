#ifndef __preferences__
#define __preferences__

#include <stdio.h>

//______________________________________________________________________________
//  Aspect ratio: 5:4

#define ASPECT_RATIO_WIDTH  5.0
#define ASPECT_RATIO_HEIGHT 4.0

//______________________________________________________________________________
//      Open GL

#define SPACE_WIDTH  ASPECT_RATIO_WIDTH  * 370
#define SPACE_HEIGHT ASPECT_RATIO_HEIGHT * 370

#ifdef VIEW_3D
//  #define Z_BUFFER
  #define BACK_FACE_CULLING
#endif

//______________________________________________________________________________
//      Window

#define WINDOW_WIDTH  ASPECT_RATIO_WIDTH * 170
#define WINDOW_HEIGHT ASPECT_RATIO_HEIGHT * 170
#define WINDOW_TITLE "Space Invaders"
#define WINDOW_POSITION_X 100 
#define WINDOW_POSITION_Y 100

//______________________________________________________________________________
//      Objects

#define BOTTOM_LINE 56.0
#define TOP_LINE    SPACE_HEIGHT - 100.0

#define HEIGHT_REFLECTION -100
#define COLLISION_ERROR 100.0

// Barriers
#define BARRIERS_NUM 4

// Cannon
#define CANNON_VELOCITY 1
#define CANNON_MAX_TIME_HIT 500

// Cannon's laser
#define CANNON_LASER_VELOCITY 2.0

// Aliens
#ifdef VIEW_3D
  #define ALIENS_ROWS 4
  #define ALIENS_COL  7
  #define SPACE_BETWEEN_ALIENS_X 100.0
  #define SPACE_BETWEEN_ALIENS_Y 100.0
#else
  #define ALIENS_ROWS 4
  #define ALIENS_COL 10
  #define SPACE_BETWEEN_ALIENS_X 50.0
  #define SPACE_BETWEEN_ALIENS_Y 70.0
#endif

#define ALIENS_VERTICAL_SHIFT -50.0
#define ALIENS_MAX_VELOCITY 0.2
#define ALIENS_MIN_VELOCITY 0.01
#define ALIENS_TIME 500         // The aliens are moving every ALIENS_TIME ms
#define ALIENS_TIME_BEWTWEEN_FIRED_KILL 250

// Aliens' lasers
#define ALIENS_LASERS_NUM 4
#define ALIENS_LASERS_TIME 3000 // The aliens shoot at least every ALIENS_LASERS_TIME ms
#define ALIENS_LASER_VELOCITY 1.0

#endif /* defined(__preferences__) */
