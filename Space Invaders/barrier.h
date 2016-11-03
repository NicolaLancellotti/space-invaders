#ifndef __Space_Invaders__barrier__
#define __Space_Invaders__barrier__

#include <stdio.h>
#include "boundingBox.h"

typedef struct {
  boundingBox_t bb;
  int life; // min = 0 -> destroyed, max = 5
} barrier_t;

//______________________________________________________________________________
#pragma mark - Init

void initBarrier(barrier_t *barrier, GLfloat x0, GLfloat y0);

//______________________________________________________________________________
#pragma mark - Draw

void drawBarrier(const barrier_t *barrier);

#endif /* defined(__Space_Invaders__barrier__) */
