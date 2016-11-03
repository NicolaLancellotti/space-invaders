#include "alien.h"
#include <stdbool.h>
#include "drawUtility.h"
#include "preferences.h"
#include "alien.h"
#include "aliens.h"
#include "collisions.h"

// _____________________________________________________________________________
#pragma mark - Declarations

static void initRectangles(const alien_t *alien, GLfloat **rectanglesBase, 
                           GLfloat **rectanglesState0, GLfloat **rectanglesState1,
                           int *rectanglesBaseNum, int *rectanglesState0Num,
                           int *rectanglesState1Num);

static void initColors(const alien_t *alien, bool reflection, GLfloat ** colorFrontBack, 
                       GLfloat ** colorLeftRight, GLfloat ** colorTopBottom);

#ifdef VIEW_3D
static void draw3D(const alien_t *alien, bool reflection);
#else
static void draw2D(const alien_t *alien);
#endif

// _____________________________________________________________________________
#pragma mark - Variables

static GLfloat scaleX = 1.0;
static GLfloat scaleY = 1.0;
static const GLfloat SPRITE_HEIGHT = 64;
static const GLfloat SPRITE_DEPTH = 40;

// _____________________________________________________________________________
#pragma mark Alien Type A

static const GLfloat SPRITE_LENGTH_A = 96;

static const int TYPE_A_RECTALGLES_BASE_NUM = 7;
// xMin, xMax, yMin, yMax
static const GLfloat TYPE_A_RECTALGLES_BASE[][4] = {
  {32, 64, 56, 64},
  { 8, 88, 48, 56},
  { 0, 24, 24, 48},
  {24, 72, 40, 48},
  {72, 96, 24, 48},
  {40, 56, 32, 40},
  {24, 72, 24, 32}
};

static const int TYPE_A_RECTALGLES_STATE_0_NUM = 7;
GLfloat TYPE_A_RECTALGLES_STATE_0[][4] = {
  {16, 40, 16, 24},
  {56, 80, 16, 24},
  { 8, 24,  8, 16},
  {40, 56,  8, 16},
  {72, 88,  8, 16},
  {16, 32,  0,  8},
  {64, 80,  0,  8}
};

static const int TYPE_A_RECTALGLES_STATE_1_NUM = 7;
GLfloat TYPE_A_RECTALGLES_STATE_1[][4] = {
  {24, 40, 16, 24},
  {56, 72, 16, 24},
  {16, 32,  8, 16},
  {40, 56,  8, 16},
  {64, 80,  8, 16},
  { 0, 16,  0,  8},
  {80, 96,  0,  8}
};

// _____________________________________________________________________________
#pragma mark Alien Type B

static const GLfloat SPRITE_LENGTH_B = 88;

static const int TYPE_B_RECTALGLES_BASE_NUM = 9;
// xMin, xMax, yMin, yMax
static const GLfloat TYPE_B_RECTALGLES_BASE[][4] = {
  {16, 24, 58, 64},
  {24, 32, 50, 58},
  {56, 64, 50, 58},
  {64, 72, 58, 64},
  {16, 72, 40, 48},
  {16, 24,  8, 48},
  {24, 64, 16, 32},
  {32, 56, 32, 40},
  {64, 72,  8, 48}
};

static const int TYPE_B_RECTALGLES_STATE_0_NUM = 6;
GLfloat TYPE_B_RECTALGLES_STATE_0[][4] = {
  {24, 40,  0,  8},
  {48, 64,  0,  8},
  { 0,  8,  8, 32},
  { 8, 16, 24, 40},
  {72, 80, 24, 40},
  {80, 88,  8, 32},
};

static const int TYPE_B_RECTALGLES_STATE_1_NUM = 6;
GLfloat TYPE_B_RECTALGLES_STATE_1[][4] = {
  {  0,  8, 24, 56},
  {  8, 16, 16, 40},
  {  8, 16,  0,  8},
  { 80, 88, 24, 56},
  { 72, 80, 16, 40},
  { 72, 80,  0,  8},
};

// _____________________________________________________________________________
#pragma mark Alien Type C

static const GLfloat SPRITE_LENGTH_C = 64;

static const int TYPE_C_RECTALGLES_BASE_NUM = 7;
// xMin, xMax, yMin, yMax
static const GLfloat TYPE_C_RECTALGLES_BASE[][4] = {
  {24, 40, 56, 64},
  {16, 48, 48, 56},
  { 8, 56, 40, 48},
  { 0, 16, 32, 40},
  {24, 40, 32, 40},
  {48, 64, 32, 40},
  { 0, 64, 32, 24}
};

static const int TYPE_C_RECTALGLES_STATE_0_NUM = 7;
GLfloat TYPE_C_RECTALGLES_STATE_0[][4] = {
  { 8, 16, 16, 24},
  { 0,  8,  8, 16},
  { 8, 16,  0,  8},
  {48, 56, 16, 24},
  {56, 64,  8, 16},
  {48, 56,  0, 8},
  {24, 40, 16, 24}
  
};

static const int TYPE_C_RECTALGLES_STATE_1_NUM = 9;
GLfloat TYPE_C_RECTALGLES_STATE_1[][4] = {
  { 0,  8,  0, 8},
  { 8, 16,  8, 16},
  {16, 24, 16, 32},
  {16, 24,  0, 8},
  {24, 40,  8, 16},
  {40, 48,  0,  8},
  {40, 48, 16, 24},
  {48, 56,  8, 16},
  {56, 64,  0,  8}
};

//______________________________________________________________________________
#pragma mark - Init

void initAlien(alien_t *alien, GLfloat x0, GLfloat y0, alienType_t type)
{    
  GLfloat length;
  switch (type) {
    case ALIEN_TYPE_A:
      length = SPRITE_LENGTH_A;
      break;
    case ALIEN_TYPE_B:
      length = SPRITE_LENGTH_B;
      break;
    case ALIEN_TYPE_C:
      length = SPRITE_LENGTH_C;
      break;
      
    default:
      break;
  }
  alien->bb.xMin = x0;
  alien->bb.xMax = x0 + length * scaleX;
  alien->bb.yMin = y0;
  alien->bb.yMax = y0 + SPRITE_HEIGHT * scaleY;
  alien->type = type;
  alien->life = ALIEN_LIFE_ALIVE;
}

void initRectangles(const alien_t *alien,GLfloat **rectanglesBase, 
                    GLfloat **rectanglesState0, GLfloat **rectanglesState1,
                    int *rectanglesBaseNum, int *rectanglesState0Num,
                    int *rectanglesState1Num)
{
  switch (alien->type) {
    case ALIEN_TYPE_A:
      *rectanglesBase   = (GLfloat *)TYPE_A_RECTALGLES_BASE;
      *rectanglesState0 = (GLfloat *)TYPE_A_RECTALGLES_STATE_0;
      *rectanglesState1 = (GLfloat *)TYPE_A_RECTALGLES_STATE_1;
      *rectanglesBaseNum   = TYPE_A_RECTALGLES_BASE_NUM;
      *rectanglesState0Num = TYPE_A_RECTALGLES_STATE_0_NUM;
      *rectanglesState1Num = TYPE_A_RECTALGLES_STATE_1_NUM;
      break;
    case ALIEN_TYPE_B:
      *rectanglesBase   = (GLfloat *)TYPE_B_RECTALGLES_BASE;
      *rectanglesState0 = (GLfloat *)TYPE_B_RECTALGLES_STATE_0;
      *rectanglesState1 = (GLfloat *)TYPE_B_RECTALGLES_STATE_1;
      *rectanglesBaseNum   = TYPE_B_RECTALGLES_BASE_NUM;
      *rectanglesState0Num = TYPE_B_RECTALGLES_STATE_0_NUM;
      *rectanglesState1Num = TYPE_B_RECTALGLES_STATE_1_NUM;
      break;
    case ALIEN_TYPE_C:
      *rectanglesBase   = (GLfloat *)TYPE_C_RECTALGLES_BASE;
      *rectanglesState0 = (GLfloat *)TYPE_C_RECTALGLES_STATE_0;
      *rectanglesState1 = (GLfloat *)TYPE_C_RECTALGLES_STATE_1;
      *rectanglesBaseNum   = TYPE_C_RECTALGLES_BASE_NUM;
      *rectanglesState0Num = TYPE_C_RECTALGLES_STATE_0_NUM;
      *rectanglesState1Num = TYPE_C_RECTALGLES_STATE_1_NUM;
      break;
    default:
      break;
  }
}

void initColors(const alien_t *alien, bool reflection, GLfloat ** colorFrontBack, 
                GLfloat **colorLeftRight, GLfloat ** colorTopBottom)
{
  switch (alien->type) {
    case ALIEN_TYPE_A:
      if (reflection && alien->life == ALIEN_LIFE_ALIVE) {
        *colorFrontBack = (GLfloat *)MY_COLOR_SKY_ALPHA_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_SKY_ALPHA_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_SKY_ALPHA_3;
      } else if (!reflection && alien->life == ALIEN_LIFE_ALIVE) {
        *colorFrontBack = (GLfloat *)MY_COLOR_SKY_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_SKY_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_SKY_3;
      } else if (reflection && alien->life == ALIEN_LIFE_FIRED) {
        *colorFrontBack = (GLfloat *)MY_COLOR_RED_ALPHA_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_RED_ALPHA_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_RED_ALPHA_3;
      } else if (!reflection && alien->life == ALIEN_LIFE_FIRED) {
        *colorFrontBack = (GLfloat *)MY_COLOR_RED_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_RED_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_RED_3;
      }
      break;
    case ALIEN_TYPE_B:
      if (reflection && alien->life == ALIEN_LIFE_ALIVE) {
        *colorFrontBack = (GLfloat *)MY_COLOR_VIOLET_ALPHA_0;
        *colorLeftRight = (GLfloat *)MY_COLOR_VIOLET_ALPHA_1;
        *colorTopBottom = (GLfloat *)MY_COLOR_VIOLET_ALPHA_3;
      } else if (!reflection && alien->life == ALIEN_LIFE_ALIVE) {
        *colorFrontBack = (GLfloat *)MY_COLOR_VIOLET_0;
        *colorLeftRight = (GLfloat *)MY_COLOR_VIOLET_1;
        *colorTopBottom = (GLfloat *)MY_COLOR_VIOLET_3;
      } else if (reflection && alien->life == ALIEN_LIFE_FIRED) {
        *colorFrontBack = (GLfloat *)MY_COLOR_RED_ALPHA_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_RED_ALPHA_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_RED_ALPHA_3;
      } else if (!reflection && alien->life == ALIEN_LIFE_FIRED) {
        *colorFrontBack = (GLfloat *)MY_COLOR_RED_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_RED_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_RED_3;
      }
      break;
    case ALIEN_TYPE_C:
      if (reflection && alien->life == ALIEN_LIFE_ALIVE) {
        *colorFrontBack = (GLfloat *)MY_COLOR_SKY_ALPHA_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_SKY_ALPHA_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_SKY_ALPHA_3;
      } else if (!reflection && alien->life == ALIEN_LIFE_ALIVE) {
        *colorFrontBack = (GLfloat *)MY_COLOR_SKY_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_SKY_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_SKY_3;
      } else if (reflection && alien->life == ALIEN_LIFE_FIRED) {
        *colorFrontBack = (GLfloat *)MY_COLOR_RED_ALPHA_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_RED_ALPHA_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_RED_ALPHA_3;
      } else if (!reflection && alien->life == ALIEN_LIFE_FIRED) {
        *colorFrontBack = (GLfloat *)MY_COLOR_RED_1;
        *colorLeftRight = (GLfloat *)MY_COLOR_RED_2;
        *colorTopBottom = (GLfloat *)MY_COLOR_RED_3;
      }
      break;
    default:
      break;
  }
}

//______________________________________________________________________________
#pragma mark - Get Set

GLfloat getAlienLengthA()
{
  return SPRITE_LENGTH_A;
}

GLfloat getAlienLengthB()
{
  return SPRITE_LENGTH_B;
}

GLfloat getAlienLengthC()
{
  return SPRITE_LENGTH_C;
}

GLfloat getAlienHeight()
{
  return SPRITE_HEIGHT;
}

int getPoints(alien_t *alien)
{
  switch (alien->type) {
    case ALIEN_TYPE_A:
      return 10;
    case ALIEN_TYPE_B:
      return 20;
    case ALIEN_TYPE_C:
      return 40;
    default:
      return 0;
  }
}

void setScaleXYAlien(GLfloat valueX, GLfloat valueY)
{
  scaleX = valueX;
  scaleY = valueY;;
}

//______________________________________________________________________________
#pragma mark - Draw

void drawAlien(const alien_t *alien)
{
#ifdef VIEW_3D
  draw3D(alien, false);
  
  //  Riflesso
  glPushMatrix();
  glTranslatef(0, 0, HEIGHT_REFLECTION);
  draw3D(alien, true);
  glPopMatrix();
#else
  draw2D(alien);
#endif
}

#if !defined(VIEW_3D)
void draw2D(const alien_t *alien)
{
  GLfloat *rectanglesBase, *rectanglesState0, *rectanglesState1;
  int rectanglesBaseNum, rectanglesState0Num, rectanglesState1Num;
  initRectangles(alien, &rectanglesBase, &rectanglesState0, &rectanglesState1,
                 &rectanglesBaseNum, &rectanglesState0Num,
                 &rectanglesState1Num);
  
  if (alien->life == ALIEN_LIFE_FIRED) {
    glColor4fv(MY_COLOR_RED_1);
  } else {
    glColor3fv(MY_COLOR_WHITE);
  }
  
  glPushMatrix();
  glTranslatef(alien->bb.xMin, alien->bb.yMin, 0);
  glBegin(GL_QUADS);
  for (int i = 0; i < rectanglesBaseNum; ++i) {
    drawRectangle(*(rectanglesBase + i * 4 + 0), *(rectanglesBase + i * 4 + 1),
                  *(rectanglesBase + i * 4 + 2), *(rectanglesBase + i * 4 + 3));
  }
  if (alien->state) {
    for (int i = 0; i < rectanglesState0Num; ++i) {
      drawRectangle(*(rectanglesState0 + i * 4 + 0), *(rectanglesState0 + i * 4 + 1),
                    *(rectanglesState0 + i * 4 + 2), *(rectanglesState0 + i * 4 + 3));
    }
  } else {
    for (int i = 0; i < rectanglesState1Num; ++i) {
      drawRectangle(*(rectanglesState1 + i * 4 + 0), *(rectanglesState1 + i * 4 + 1),
                    *(rectanglesState1 + i * 4 + 2), *(rectanglesState1 + i * 4 + 3));
    }
  }
  glEnd();
  glPopMatrix();
}
#endif

void draw3D(const alien_t *alien, bool reflection)
{
  GLfloat *rectanglesBase, *rectanglesState0, *rectanglesState1;
  int rectanglesBaseNum, rectanglesState0Num, rectanglesState1Num;
  initRectangles(alien, &rectanglesBase, &rectanglesState0, &rectanglesState1,
                 &rectanglesBaseNum, &rectanglesState0Num,
                 &rectanglesState1Num);
  
  GLfloat *colorFrontBack, *colorLeftRight, *colorTopBottom;
  initColors(alien, reflection, &colorFrontBack, &colorLeftRight, &colorTopBottom);
  
  
  glPushMatrix();
  glTranslatef(alien->bb.xMin, alien->bb.yMin, 0);
  glScaled(scaleX,  scaleY, 1);
  for (int i = 0; i < rectanglesBaseNum; ++i) {
    drawParallelepiped(*(rectanglesBase + i * 4 + 0), *(rectanglesBase + i * 4 + 1),
                       *(rectanglesBase + i * 4 + 2), *(rectanglesBase + i * 4 + 3), SPRITE_DEPTH,
                       colorFrontBack, colorLeftRight, colorTopBottom);
  }
  if (alien->state) {
    for (int i = 0; i < rectanglesState0Num; ++i) {
      drawParallelepiped(*(rectanglesState0 + i * 4 + 0), *(rectanglesState0 + i * 4 + 1),
                         *(rectanglesState0 + i * 4 + 2), *(rectanglesState0 + i * 4 + 3), SPRITE_DEPTH,
                         colorFrontBack, colorLeftRight, colorTopBottom);
      
    }
  } else {
    for (int i = 0; i < rectanglesState1Num; ++i) {
      drawParallelepiped(*(rectanglesState1 + i * 4 + 0), *(rectanglesState1 + i * 4 + 1),
                         *(rectanglesState1 + i * 4 + 2), *(rectanglesState1 + i * 4 + 3), SPRITE_DEPTH,
                         colorFrontBack, colorLeftRight, colorTopBottom);
      
    }
  }
  glPopMatrix();
  
}

//______________________________________________________________________________
#pragma mark - Other

void nextStateAlien(alien_t *alien)
{
  alien->state = (alien->state + 1) % 2;
}
