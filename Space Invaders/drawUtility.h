#ifndef __Space_Invaders__utillity__
#define __Space_Invaders__utillity__

#include <stdio.h>
#include "glutCrossPlatform.h"
#include "aliens.h"
#include "barrier.h"

//______________________________________________________________________________
#pragma mark - Variables

extern const GLfloat MY_COLOR_GREEN_1[];
extern const GLfloat MY_COLOR_GREEN_2[];
extern const GLfloat MY_COLOR_GREEN_3[];
extern const GLfloat MY_COLOR_SKY_1[];
extern const GLfloat MY_COLOR_SKY_2[];
extern const GLfloat MY_COLOR_SKY_3[];
extern const GLfloat MY_COLOR_GRAY_1[];
extern const GLfloat MY_COLOR_GRAY_2[];
extern const GLfloat MY_COLOR_GRAY_3[];
extern const GLfloat MY_COLOR_ORANGE_1[];
extern const GLfloat MY_COLOR_ORANGE_2[];
extern const GLfloat MY_COLOR_ORANGE_3[];
extern const GLfloat MY_COLOR_YELLOW_1[];
extern const GLfloat MY_COLOR_YELLOW_2[];
extern const GLfloat MY_COLOR_YELLOW_3[];
extern const GLfloat MY_COLOR_RED_1[];
extern const GLfloat MY_COLOR_RED_2[];
extern const GLfloat MY_COLOR_RED_3[];
extern const GLfloat MY_COLOR_VIOLET_0[];
extern const GLfloat MY_COLOR_VIOLET_1[];
extern const GLfloat MY_COLOR_VIOLET_3[];
extern const GLfloat MY_COLOR_WHITE[];
extern const GLfloat MY_COLOR_BLU_1[];

extern const GLfloat MY_COLOR_GREEN_ALPHA_1[];
extern const GLfloat MY_COLOR_GREEN_ALPHA_2[];
extern const GLfloat MY_COLOR_GREEN_ALPHA_3[];
extern const GLfloat MY_COLOR_SKY_ALPHA_1[];
extern const GLfloat MY_COLOR_SKY_ALPHA_2[];
extern const GLfloat MY_COLOR_SKY_ALPHA_3[];
extern const GLfloat MY_COLOR_GRAY_ALPHA_1[];
extern const GLfloat MY_COLOR_GRAY_ALPHA_2[];
extern const GLfloat MY_COLOR_GRAY_ALPHA_3[];
extern const GLfloat MY_COLOR_ORANGE_ALPHA_1[];
extern const GLfloat MY_COLOR_ORANGE_ALPHA_2[];
extern const GLfloat MY_COLOR_ORANGE_ALPHA_3[];
extern const GLfloat MY_COLOR_YELLOW_ALPHA_1[];
extern const GLfloat MY_COLOR_YELLOW_ALPHA_2[];
extern const GLfloat MY_COLOR_YELLOW_ALPHA_3[];
extern const GLfloat MY_COLOR_RED_ALPHA_1[];
extern const GLfloat MY_COLOR_RED_ALPHA_2[];
extern const GLfloat MY_COLOR_RED_ALPHA_3[];
extern const GLfloat MY_COLOR_VIOLET_ALPHA_0[];
extern const GLfloat MY_COLOR_VIOLET_ALPHA_1[];
extern const GLfloat MY_COLOR_VIOLET_ALPHA_3[];
extern const GLfloat MY_COLOR_BLU_ALPHA_1[];

//______________________________________________________________________________
#pragma mark - Draw Shape

////  Invoke between glBegin(GL_QUADS) and glEnd()
//#define drawRectangle(xMin, xMax, yMin, yMax) \
//    glVertex2f(xMin, yMin); \
//    glVertex2f(xMax, yMin); \
//    glVertex2f(xMax, yMax); \
//    glVertex2f(xMin, yMax); 

//  Invoke between glBegin(GL_QUADS) e glEnd()
void drawRectangle(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax);

//  Invoke outside glBegin(GL_QUADS) and glEnd()
void drawParallelepiped(GLfloat xMin, GLfloat  xMax, GLfloat yMin, GLfloat yMax, 
                        GLfloat depth,
                        const GLfloat colorFrontBack[],
                        const GLfloat colorLeftRight[],
                        const GLfloat colorTopBottom[]);

//______________________________________________________________________________
#pragma mark - Other

void drawBottomLine(void);
void drawTopLine(void);
void drawBackGround(void);
void drawBoundingBoxs(const cannon_t *cannon, const barrier_t barriers[], 
                      const aliens_t *aliens);

#endif /* defined(__Space_Invaders__utillity__) */
