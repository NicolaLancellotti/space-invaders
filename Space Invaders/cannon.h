#ifndef __Space_Invaders__cannon__
#define __Space_Invaders__cannon__

#include <stdio.h>
#include <stdbool.h>
#include "glutCrossPlatform.h"
#include "boundingBox.h"

typedef struct {
  boundingBox_t bb;
  bool fire;
  bool right;
  bool left;
  int time; // Last moving time
  int timeHit;
} cannon_t;

//______________________________________________________________________________
#pragma mark - Init

void initCannon(cannon_t *cannon, GLfloat x0, GLfloat y0);

//______________________________________________________________________________
#pragma mark - Update

void updateCannon(cannon_t *cannon);

//______________________________________________________________________________
#pragma mark - Draw

void drawCannon(const cannon_t *cannon);

#endif /* defined(__Space_Invaders__cannon__) */
