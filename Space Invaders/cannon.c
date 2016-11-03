#include "cannon.h"
#include "drawUtility.h"
#include "preferences.h"

// _____________________________________________________________________________
#pragma mark - Declarations

static void shiftCannonHorizontal(cannon_t *cannon, GLfloat shift);

// _____________________________________________________________________________
#pragma mark - Variables

static const GLfloat SPRITE_LENGTH = 104;
static const GLfloat SPRITE_HEIGHT = 64;
__attribute__((unused)) static const GLfloat SPRITE_DEPTH = 40;

static const int RECTALGLES_NUM = 4;
// xMin, xMax, yMin, yMax
static const GLfloat rectangles[][4] = {
  {48,  56, 56, 64}, // 1
  {40,  64, 40, 56}, // 2
  { 8,  96, 32, 40}, // 3
  { 0, 104,  0, 32}, // 4
};

//______________________________________________________________________________
#pragma mark - Init

void initCannon(cannon_t * cannon, GLfloat x0, GLfloat y0)
{
  cannon->bb.xMin = x0;
  cannon->bb.xMax = x0 + SPRITE_LENGTH;
  cannon->bb.yMin = y0;
  cannon->bb.yMax = y0 + SPRITE_HEIGHT;
  cannon->timeHit = 0;
}

//______________________________________________________________________________
#pragma mark - Update

void shiftCannonHorizontal(cannon_t *cannon, GLfloat velocity)
{    
  GLfloat now = glutGet(GLUT_ELAPSED_TIME);
  GLfloat space = velocity * (now - cannon->time);
  cannon->time = now;
  cannon->bb.xMin += space;
  cannon->bb.xMax += space;
}

void updateCannon(cannon_t *cannon)
{
  int now = glutGet(GLUT_ELAPSED_TIME);
  
  if (now - cannon->timeHit > CANNON_MAX_TIME_HIT) {
    cannon->timeHit = 0;
  }
  
  if (cannon->right && cannon->bb.xMin + 60 < SPACE_WIDTH) {
    shiftCannonHorizontal(cannon, CANNON_VELOCITY);
  }
  if (cannon->left && cannon->bb.xMax - 60 > 0) {
    shiftCannonHorizontal(cannon, - CANNON_VELOCITY);
  }
}

//______________________________________________________________________________
#pragma mark - Draw

void drawCannon(const cannon_t *cannon)
{    
  glPushMatrix();
  glTranslatef(cannon->bb.xMin, cannon->bb.yMin, 0);
#ifdef VIEW_3D
  GLfloat *color1, *color2, *color3;
  GLfloat *color1Alpha, *color2Alpha, *color3Alpha;
  if (cannon->timeHit == 0) {
    color1 = (GLfloat *)MY_COLOR_GRAY_1;
    color2 = (GLfloat *)MY_COLOR_GRAY_2;
    color3 = (GLfloat *)MY_COLOR_GRAY_3;
    color1Alpha = (GLfloat *)MY_COLOR_GRAY_ALPHA_1;
    color2Alpha = (GLfloat *)MY_COLOR_GRAY_ALPHA_2;
    color3Alpha = (GLfloat *)MY_COLOR_GRAY_ALPHA_3;
  } else {
    color1 = (GLfloat *)MY_COLOR_RED_1;
    color2 = (GLfloat *)MY_COLOR_RED_2;
    color3 = (GLfloat *)MY_COLOR_RED_3;
    color1Alpha = (GLfloat *)MY_COLOR_RED_ALPHA_1;
    color2Alpha = (GLfloat *)MY_COLOR_RED_ALPHA_2;
    color3Alpha = (GLfloat *)MY_COLOR_RED_ALPHA_3;
  }
  
  for (int i = 0; i < RECTALGLES_NUM; ++i) {
    drawParallelepiped(rectangles[i][0], rectangles[i][1],
                       rectangles[i][2], rectangles[i][3], SPRITE_DEPTH,
                       color1, color2, color3);
  }
  
  //    Reflection
  glTranslatef(0, 0, -100);
  for (int i = 0; i < RECTALGLES_NUM; ++i) {
    drawParallelepiped(rectangles[i][0], rectangles[i][1],
                       rectangles[i][2], rectangles[i][3], SPRITE_DEPTH,
                       color1Alpha, color2Alpha, color3Alpha);
  }
#else
  if (cannon->timeHit == 0) {
    glColor3fv(MY_COLOR_GREEN_1);
  } else {
    glColor3fv(MY_COLOR_RED_1);
  }
  
  glBegin(GL_QUADS);
  for (int i = 0; i < RECTALGLES_NUM; ++i) {
    drawRectangle(rectangles[i][0], rectangles[i][1],
                  rectangles[i][2], rectangles[i][3]);
  }
  glEnd();
#endif
  glPopMatrix();
}
