#include "barrier.h"
#include "preferences.h"
#include "drawUtility.h"

//______________________________________________________________________________
#pragma mark - Variables

static const GLfloat SPRITE_LENGTH = 176;
static const GLfloat SPRITE_HEIGHT = 128;
__attribute__((unused)) static const GLfloat SPRITE_DEPTH = 40;

static const int RECTALGLES_NUM = 11;
// xMin, xMax, yMin, yMax
static const GLfloat rectangles[][4] = {
  {32,  144, 120, 128},  // 01
  {24,  152, 112, 120},  // 02
  {16,  160, 104, 112},  // 03
  {8,   168,  96, 104},  // 04
  {0,   176,  32,  96},  // 05
  {0,    56,  24,  32},  // 06
  {120, 176,  24,  32},  // 07
  {0,    48,  16,  24},  // 08
  {128, 176,  16,  24},  // 09
  {0,    40,   0,  16},  // 10
  {136, 176,   0,  16}   // 11
};

//______________________________________________________________________________
#pragma mark - Init

void initBarrier(barrier_t *barrier, GLfloat x0, GLfloat y0)
{
  barrier->bb.xMin = x0;
  barrier->bb.xMax = x0 + SPRITE_LENGTH;
  barrier->bb.yMin = y0;
  barrier->bb.yMax = y0 + SPRITE_HEIGHT;
  
  barrier->life = 5;
}

//______________________________________________________________________________
#pragma mark - Draw

void drawBarrier(const barrier_t *barrier)
{
  GLfloat *color1, *color2, *color3;
  GLfloat *color1Alpha, *color2Alpha, *color3Alpha;
  switch (barrier->life) {
    case 5:
      glColor4fv(MY_COLOR_BLU_1);
      color1 = (GLfloat *)MY_COLOR_VIOLET_0;
      color2 = (GLfloat *)MY_COLOR_VIOLET_1;
      color3 = (GLfloat *)MY_COLOR_VIOLET_3;
      color1Alpha = (GLfloat *)MY_COLOR_VIOLET_ALPHA_0;
      color2Alpha = (GLfloat *)MY_COLOR_VIOLET_ALPHA_1;
      color3Alpha = (GLfloat *)MY_COLOR_VIOLET_ALPHA_3;
      break;
    case 4:
      glColor4fv(MY_COLOR_GREEN_1);
      color1 = (GLfloat *)MY_COLOR_GREEN_1;
      color2 = (GLfloat *)MY_COLOR_GREEN_2;
      color3 = (GLfloat *)MY_COLOR_GREEN_3;
      color1Alpha = (GLfloat *)MY_COLOR_GREEN_ALPHA_1;
      color2Alpha = (GLfloat *)MY_COLOR_GREEN_ALPHA_2;
      color3Alpha = (GLfloat *)MY_COLOR_GREEN_ALPHA_3;
      break;
    case 3:
      glColor4fv(MY_COLOR_YELLOW_1);
      color1 = (GLfloat *)MY_COLOR_YELLOW_1;
      color2 = (GLfloat *)MY_COLOR_YELLOW_2;
      color3 = (GLfloat *)MY_COLOR_YELLOW_3;
      color1Alpha = (GLfloat *)MY_COLOR_YELLOW_ALPHA_1;
      color2Alpha = (GLfloat *)MY_COLOR_YELLOW_ALPHA_2;
      color3Alpha = (GLfloat *)MY_COLOR_YELLOW_ALPHA_3;
      break;
    case 2:
      glColor4fv(MY_COLOR_ORANGE_1);
      color1 = (GLfloat *)MY_COLOR_ORANGE_1;
      color2 = (GLfloat *)MY_COLOR_ORANGE_2;
      color3 = (GLfloat *)MY_COLOR_ORANGE_3;
      color1Alpha = (GLfloat *)MY_COLOR_ORANGE_ALPHA_1;
      color2Alpha = (GLfloat *)MY_COLOR_ORANGE_ALPHA_2;
      color3Alpha = (GLfloat *)MY_COLOR_ORANGE_ALPHA_3;
      break;
    case 1:
      glColor4fv(MY_COLOR_RED_1);
      color1 = (GLfloat *)MY_COLOR_RED_1;
      color2 = (GLfloat *)MY_COLOR_RED_2;
      color3 = (GLfloat *)MY_COLOR_RED_3;
      color1Alpha = (GLfloat *)MY_COLOR_RED_ALPHA_1;
      color2Alpha = (GLfloat *)MY_COLOR_RED_ALPHA_2;
      color3Alpha = (GLfloat *)MY_COLOR_RED_ALPHA_3;
      break;
    default:
      // barrier destroyed
      return;
  }
  
  glPushMatrix();
  glTranslatef(barrier->bb.xMin, barrier->bb.yMin, 0);
#ifdef VIEW_3D
  for (int i = 0; i < RECTALGLES_NUM; ++i) {
    drawParallelepiped(rectangles[i][0], rectangles[i][1],
                       rectangles[i][2], rectangles[i][3], SPRITE_DEPTH,
                       color1, color2, color3);
  }
  
  // Reflection
  glTranslatef(0, 0, HEIGHT_REFLECTION);
  for (int i = 0; i < RECTALGLES_NUM; ++i) {
    drawParallelepiped(rectangles[i][0], rectangles[i][1],
                       rectangles[i][2], rectangles[i][3], SPRITE_DEPTH,
                       color1Alpha, color2Alpha, color3Alpha);
  }
#else
  glBegin(GL_QUADS);
  for (int i = 0; i < RECTALGLES_NUM; ++i) {
    drawRectangle(rectangles[i][0], rectangles[i][1],
                  rectangles[i][2], rectangles[i][3]);
  }
  glEnd();
#endif
  glPopMatrix();
}
