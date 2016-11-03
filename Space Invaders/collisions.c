#include <math.h>
#include "collisions.h"

static GLfloat lengthCommonSegment(GLdouble min1, GLdouble max1, GLdouble min2, GLdouble max2)
{
  GLfloat length1 = fabs(max1 - min1);
  GLfloat length2 = fabs(max2 - min2);
  GLfloat lowerExtreme = min1 < min2 ? min1 : min2;
  GLfloat higherExtreme = max1 > max2 ? max1 : max2;
  GLfloat length = length1 + length2 - fabs(higherExtreme - lowerExtreme);
  return length;
}

bool isCollision(const boundingBox_t bb1, const boundingBox_t bb2, GLfloat error)
{
  GLfloat base = lengthCommonSegment(bb1.xMin, bb1.xMax, bb2.xMin, bb2.xMax);
  GLfloat height = lengthCommonSegment(bb1.yMin  -  error, bb1.yMax + error, bb2.yMin, bb2.yMax);
  return base > 0 && height > 0; // -> area > 0 -> collision
}
