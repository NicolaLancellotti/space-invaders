#ifndef __Space_Invaders__collisions__
#define __Space_Invaders__collisions__

#include <stdio.h>
#include <stdbool.h>
#include "glutCrossPlatform.h"
#include "boundingBox.h"

bool isCollision(const boundingBox_t bb1, const boundingBox_t bb2, GLfloat error);

#endif /* defined(__Space_Invaders__collisions__) */
