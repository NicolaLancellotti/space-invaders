#include "drawUtility.h"
#include "preferences.h"

//______________________________________________________________________________
#pragma mark - Variables

#define ALPHA 0.1

const GLfloat MY_COLOR_ORANGE_1[] = {1.00, 0.57, 0.00, 1.0};
const GLfloat MY_COLOR_ORANGE_2[] = {0.93, 0.53, 0.00, 1.0};
const GLfloat MY_COLOR_ORANGE_3[] = {0.81, 0.46, 0.00, 1.0};
const GLfloat MY_COLOR_RED_1[]    = {1.00, 0.00, 0.00, 1.0};
const GLfloat MY_COLOR_RED_2[]    = {0.89, 0.00, 0.00, 1.0};
const GLfloat MY_COLOR_RED_3[]    = {0.72, 0.00, 0.00, 1.0};
const GLfloat MY_COLOR_GREEN_1[]  = {0.00, 1.00, 0.10, 1.0};
const GLfloat MY_COLOR_GREEN_2[]  = {0.00, 0.75, 0.07, 1.0};
const GLfloat MY_COLOR_GREEN_3[]  = {0.00, 0.34, 0.02, 1.0};
const GLfloat MY_COLOR_BLU_1[]    = {0.00, 0.00, 1.00, 1.0};
const GLfloat MY_COLOR_SKY_1[]    = {0.42, 0.71, 1.00, 1.0};
const GLfloat MY_COLOR_SKY_2[]    = {0.27, 0.47, 0.68, 1.0};
const GLfloat MY_COLOR_SKY_3[]    = {0.19, 0.35, 0.50, 1.0};
const GLfloat MY_COLOR_YELLOW_1[] = {1.00, 1.00, 0.00, 1.0};
const GLfloat MY_COLOR_YELLOW_2[] = {0.91, 0.91, 0.01, 1.0};
const GLfloat MY_COLOR_YELLOW_3[] = {0.77, 0.77, 0.01, 1.0};
const GLfloat MY_COLOR_VIOLET_0[] = {0.75, 0.61, 0.97, 1.0};
const GLfloat MY_COLOR_VIOLET_1[] = {0.60, 0.49, 0.80, 1.0};
const GLfloat MY_COLOR_VIOLET_3[] = {0.33, 0.26, 0.44, 1.0};
const GLfloat MY_COLOR_GRAY_1[]   = {0.95, 0.95, 0.95, 1.0};
const GLfloat MY_COLOR_GRAY_2[]   = {0.73, 0.73, 0.73, 1.0};
const GLfloat MY_COLOR_GRAY_3[]   = {0.31, 0.31, 0.31, 1.0};
const GLfloat MY_COLOR_WHITE[]    = {1.00, 1.00, 1.00, 1.0};

const GLfloat MY_COLOR_ORANGE_ALPHA_1[] = {1.00, 0.57, 0.00, ALPHA};
const GLfloat MY_COLOR_ORANGE_ALPHA_2[] = {0.93, 0.53, 0.00, ALPHA};
const GLfloat MY_COLOR_ORANGE_ALPHA_3[] = {0.81, 0.46, 0.00, ALPHA};
const GLfloat MY_COLOR_RED_ALPHA_1[]    = {1.00, 0.00, 0.00, ALPHA};
const GLfloat MY_COLOR_RED_ALPHA_2[]    = {0.89, 0.00, 0.00, ALPHA};
const GLfloat MY_COLOR_RED_ALPHA_3[]    = {0.72, 0.00, 0.00, ALPHA};
const GLfloat MY_COLOR_GREEN_ALPHA_1[]  = {0.00, 1.00, 0.10, ALPHA};
const GLfloat MY_COLOR_GREEN_ALPHA_2[]  = {0.00, 0.75, 0.07, ALPHA};
const GLfloat MY_COLOR_GREEN_ALPHA_3[]  = {0.00, 0.34, 0.02, ALPHA};
const GLfloat MY_COLOR_BLU_ALPHA_1[]    = {0.00, 0.00, 1.00, ALPHA};
const GLfloat MY_COLOR_SKY_ALPHA_1[]    = {0.42, 0.71, 1.00, ALPHA};
const GLfloat MY_COLOR_SKY_ALPHA_2[]    = {0.27, 0.47, 0.68, ALPHA};
const GLfloat MY_COLOR_SKY_ALPHA_3[]    = {0.19, 0.35, 0.50, ALPHA};
const GLfloat MY_COLOR_YELLOW_ALPHA_1[] = {1.00, 1.00, 0.00, ALPHA};
const GLfloat MY_COLOR_YELLOW_ALPHA_2[] = {0.91, 0.91, 0.01, ALPHA};
const GLfloat MY_COLOR_YELLOW_ALPHA_3[] = {0.77, 0.77, 0.01, ALPHA};
const GLfloat MY_COLOR_VIOLET_ALPHA_0[] = {0.75, 0.61, 0.97, ALPHA};
const GLfloat MY_COLOR_VIOLET_ALPHA_1[] = {0.60, 0.49, 0.80, ALPHA};
const GLfloat MY_COLOR_VIOLET_ALPHA_3[] = {0.33, 0.26, 0.44, ALPHA};
const GLfloat MY_COLOR_GRAY_ALPHA_1[]   = {0.95, 0.95, 0.95, ALPHA};
const GLfloat MY_COLOR_GRAY_ALPHA_2[]   = {0.73, 0.73, 0.73, ALPHA};
const GLfloat MY_COLOR_GRAY_ALPHA_3[]   = {0.31, 0.31, 0.31, ALPHA};

// Vertex Array
GLfloat vertices[] = {
  -0.5, -0.5, -0.5,
  0.5, -0.5, -0.5,
  0.5,  0.5, -0.5,
  -0.5,  0.5, -0.5,
  -0.5, -0.5,  0.5,
  0.5, -0.5,  0.5,
  0.5,  0.5,  0.5,
  -0.5,  0.5,  0.5
};

GLubyte frontFace[]  = {4, 5, 6, 7}; 
GLubyte backFace[]   = {0, 3, 2, 1};
GLubyte leftFace[]   = {0, 4, 7, 3}; 
GLubyte rightFace[]  = {1, 2, 6, 5}; 
GLubyte topFace[]    = {2, 3, 7, 6}; 
GLubyte bottomFace[] = {0, 1, 5, 4};

//______________________________________________________________________________
#pragma mark - Draw Shape

void drawRectangle(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax)
{
  glVertex2f(xMin, yMin);
  glVertex2f(xMax, yMin);
  glVertex2f(xMax, yMax);
  glVertex2f(xMin, yMax);
}

void drawParallelepiped(GLfloat xMin, GLfloat  xMax,GLfloat  yMin, GLfloat yMax, 
                        GLfloat depth,
                        const GLfloat *colorFrontBack,
                        const GLfloat colorLeftRight[],
                        const GLfloat colorTopBottom[])
{
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  
  GLfloat x = xMax - xMin;
  GLfloat y = yMax - yMin;
  
  glPushMatrix();
  glTranslatef(x / 2.0 + xMin, y / 2.0 + yMin, -depth / 2);
  glScalef(x, y, depth);
  
  glColor4fv(colorTopBottom);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomFace);
  
  glColor4fv(colorLeftRight);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightFace);
  
  glColor4fv(colorFrontBack);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backFace);
  
  glPopMatrix();
}

//______________________________________________________________________________
#pragma mark - Other

void drawBottomLine()
{
  glColor3fv(MY_COLOR_GREEN_1);
  glBegin(GL_LINE_LOOP);
  glVertex2f(0, BOTTOM_LINE);
  glVertex2f(SPACE_WIDTH, BOTTOM_LINE);
  glEnd();
}

void drawTopLine()
{
  glColor3fv(MY_COLOR_GREEN_1);
  glBegin(GL_LINE_LOOP);
  glVertex2f(0,  TOP_LINE);
  glVertex2f(SPACE_WIDTH, TOP_LINE);
  glEnd();
}

void drawBackGround()
{
  glShadeModel(GL_SMOOTH);
  
  glPushMatrix();
  glTranslatef(0, 0, -1850);
  glRotatef(-10, 0, 0, 1);
  glScaled(2000, 2000, 1);
  
  glBegin(GL_QUADS);
  glColor3f(0.29, 0.02, 0.02);
  glVertex3f(-1.5, -1.5, 0);
  glVertex3f( 1.5, -1.5, 0);
  
  glColor3f(0.01, 0.13, 0.40);
  glVertex3f( 1.5,  1.5, 0);
  glVertex3d(-1.5, 1.5, 0);
  glEnd();
  
  glPopMatrix();
  
  glShadeModel(GL_FLAT);
}

void drawBoundingBoxs(const cannon_t *cannon, const barrier_t barriers[], 
                      const aliens_t *aliens)
{
  drawBoundingBox(&cannon->bb);
  for (int i = 0; i < BARRIERS_NUM; ++i) {
    drawBoundingBox(&barriers[i].bb);
  }
  for (int row = aliens->topRow; row <= aliens->bottomRow; ++row ) {
    for (int col = aliens->leftCol; col <= aliens->rightCol; ++col ) {
      drawBoundingBox(&aliens->matrix[row][col].bb);
    }
  }
  drawBoundingBox(&aliens->bb);
}
