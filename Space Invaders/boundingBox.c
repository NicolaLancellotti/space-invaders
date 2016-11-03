#include "boundingBox.h"
#include "drawUtility.h"

void drawBoundingBox(const boundingBox_t *boundingBox)
{
  glColor4fv(MY_COLOR_WHITE);
  glBegin(GL_LINE_LOOP);
  glVertex2f(boundingBox->xMin, boundingBox->yMin);
  glVertex2f(boundingBox->xMax, boundingBox->yMin);
  glVertex2f(boundingBox->xMax, boundingBox->yMax);
  glVertex2f(boundingBox->xMin, boundingBox->yMax);
  glEnd();
}
