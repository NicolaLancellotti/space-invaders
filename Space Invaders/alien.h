#ifndef __Space_Invaders__alien__
#define __Space_Invaders__alien__

#include <stdio.h>
#include "glutCrossPlatform.h"
#include "boundingBox.h"

typedef enum {
  ALIEN_LIFE_ALIVE,
  ALIEN_LIFE_FIRED,
  ALIEN_LIFE_DEAD
} alienLife_t;

typedef enum {
  ALIEN_TYPE_A,
  ALIEN_TYPE_B,
  ALIEN_TYPE_C,
} alienType_t;

typedef struct {
  boundingBox_t bb;
  alienLife_t life;
  int state; // 0 or 1
  alienType_t type;
  int timeFired;
} alien_t;

//______________________________________________________________________________
#pragma mark - Init

void initAlien(alien_t *alien, GLfloat x0, GLfloat y0, alienType_t type);

//______________________________________________________________________________
#pragma mark - Get & Set

GLfloat getAlienLengthA(void);
GLfloat getAlienLengthB(void);
GLfloat getAlienLengthC(void);
GLfloat getAlienHeight(void);
int getPoints(alien_t *alien);
void setScaleXYAlien(GLfloat valueX, GLfloat valueY);

//______________________________________________________________________________
#pragma mark - Draw

void drawAlien(const alien_t *alien);

//______________________________________________________________________________
#pragma mark - Other

void nextStateAlien(alien_t *alien);

#endif /* defined(__Space_Invaders__alien__) */
