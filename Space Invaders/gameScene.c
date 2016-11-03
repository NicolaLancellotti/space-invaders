#include <stdlib.h>
#include "gameScene.h"
#include "glutCrossPlatform.h"
#include "drawUtility.h"
#include "collisions.h"
#include "preferences.h"
#include "cannon.h"
#include "aliens.h"
#include "laser.h"
//#define DRAW_BOUNDING_BOX

// _____________________________________________________________________________
#pragma mark - Declarations

// Update state of the game
static void initObjectsForNewGame(void);
static void initObjectsForNextLife(void);
static void initObjectsForNextLevel(void);

// Callbacks
static void dispalyCallback(void);
static void reshapeCallBack(int width, int height);
static void idleCallBack(void);
static void keyboardCallback(unsigned char c, int x, int y);
static void keyboardUpCallback(unsigned char key, int x, int y);
static void specialCallback(int key, int x, int y);
static void specialUpCallback(int key, int x, int y);
static void menuCallBack(int value);

static void createMenu(void);

//______________________________________________________________________________
#pragma mark - Variables

static game_t game;
static cannon_t cannon;
static laser_t cannonLaser; 
static barrier_t barriers[BARRIERS_NUM];
static aliens_t aliens;
static laser_t aliensLasers[ALIENS_LASERS_NUM];
static int aliensLasersTime; // ulima volta che un alieno ha sparato un laser

static int menu;

//______________________________________________________________________________
#pragma mark - Update state of the game

void initObjectsForNewGame()
{
#ifdef VIEW_3D
  setScaleXYAlien(1.25, 1.25);
#endif
  
  initGame(&game);
  initObjectsForNextLife();
  
  //    Barriers
  GLfloat length = 176;
  GLfloat shift = (SPACE_WIDTH - length * BARRIERS_NUM) / (BARRIERS_NUM + 1);
  for (int i = 0; i < BARRIERS_NUM; ++i) {
    initBarrier(&barriers[i], shift * (i + 1) + length * i, 350);
  }
  
  for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
    aliensLasers[i].fired = false;
  }
  
  initObjectsForNextLevel();
}

void initObjectsForNextLevel()
{
  game.lives++;
  game.state = GAME_STATE_PLAY;
  
  //    Aliens
  GLfloat heightAlien = getAlienHeight();
  GLfloat spaceY1 = SPACE_HEIGHT - 200;
  GLfloat spaceY = heightAlien + SPACE_BETWEEN_ALIENS_Y;
  
  for (int row = 0; row < ALIENS_ROWS; ++row) {
    GLfloat lengthAlien = 0;
    GLfloat spaceBe = getAlienLengthA();
    alienType_t type = ALIEN_TYPE_A;
    
    if (row == 1 || row == 0) {
      type = ALIEN_TYPE_B;
      lengthAlien = getAlienLengthB();
    }
    if (row == 2 || row == 3) {
      type = ALIEN_TYPE_A;
      lengthAlien = getAlienLengthA();
    }
    spaceBe = SPACE_BETWEEN_ALIENS_X - lengthAlien + getAlienLengthA();
    GLfloat spaceX1 = (SPACE_WIDTH - (lengthAlien * ALIENS_COL + spaceBe * (ALIENS_COL - 1))) / 2 ;
    GLfloat spaceX = lengthAlien + spaceBe;
    for (int col = 0; col < ALIENS_COL; ++col) {
      
      initAlien(&aliens.matrix[row][col], spaceX1 + col * spaceX, spaceY1 - row * spaceY, type);
    }
  }
  initAliens(&aliens);
  
  cannonLaser.fired = false;
  for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
    aliensLasers[i].fired = false;
  }
}

void initObjectsForNextLife()
{
  initCannon(&cannon,  SPACE_WIDTH / 2 - 104 / 2 , BOTTOM_LINE + 30);
}


//______________________________________________________________________________
#pragma mark - Callbacks

void dispalyCallback(void)
{
  
#ifdef Z_BUFFER
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#else
  glClear(GL_COLOR_BUFFER_BIT);
#endif 
  
  glLoadIdentity();
  
#ifdef VIEW_3D
  drawBackGround();
  drawHUD(&game);
  
  //    Camera
  glRotatef(-40, 1, 0, 0);
  glRotatef(-10, 0, 0, 1);
  glTranslatef(-SPACE_WIDTH / 2.0 -200, -SPACE_HEIGHT / 2.0 + 900, -650);
#else
  drawBottomLine();
  drawHUD(&game);
#endif
  
  drawCannon(&cannon);
  drawLaser(&cannonLaser);
  
  drawAliens(&aliens);
  for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
    drawLaser(&aliensLasers[i]);
  }
  
  for (int i = 0; i < BARRIERS_NUM; ++i) {
    drawBarrier(&barriers[i]);
  }
  
#ifdef DRAW_BOUNDING_BOX
  drawBoundingBoxs(&cannon, barriers, &aliens);
#endif
  
  glutSwapBuffers();
}

void reshapeCallBack(int width, int height)
{
  GLfloat w = height * 5.0 / 4.0;
  GLfloat h = width * 4.0 / 5.0;
  if (width >= w) {
    glViewport((width - w)/2.0, 0, w, height);
  }
  else {
    glViewport(0, (height - h)/2.0, width, h);
  }
}

void idleCallBack(void)
{
  updateCannon(&cannon);
  updateCannonLaser(&cannonLaser, &cannon, barriers, &aliens, &game);
  
  bool lifeLost = false;
  if (updateAliens(&aliens, &cannon, barriers, &game)) {
    lifeLost = true;
  }
  if (updateAliensLasers(aliensLasers, &aliensLasersTime, &aliens, barriers, &cannon, &game)) {
    lifeLost = true;
  }
  
  switch (game.state) {
    case GAME_STATE_GAME_OVER:
      glutIdleFunc(NULL);
      cannon.timeHit = glutGet(GLUT_ELAPSED_TIME);
      break;
    case GAME_STATE_WIN:
      initObjectsForNextLevel();
      break;
    case GAME_STATE_PLAY:
      if (lifeLost) {
        initObjectsForNextLife();
        cannon.timeHit = glutGet(GLUT_ELAPSED_TIME);
      }
    default:
      break;
  }
  
  glutPostRedisplay();
}

void keyboardCallback(unsigned char c, int x, int y)
{
  int now = glutGet(GLUT_ELAPSED_TIME);
  switch (c) {
    case ' ':
      //Fire
      if (game.state == GAME_STATE_PLAY) {
        cannon.fire = true;
      }
      break;
    case 'p':
    case 'P':
      // Pause
      if (game.state == GAME_STATE_PAUSE) {
        game.state = GAME_STATE_PLAY;
        cannon.time = aliens.time =  cannonLaser.time = now;
        for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
          aliensLasers[i].time = now;
        }
        glutIdleFunc(idleCallBack);
      } else if (game.state == GAME_STATE_PLAY){
        game.state = GAME_STATE_PAUSE;
        glutIdleFunc(NULL);
      }
      break;
    case 'n':
    case 'N':
      // New game
      initObjectsForNewGame();
      glutIdleFunc(idleCallBack);
      break;
    case 'q':
    case 'Q':
      // Quit
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
  if (key == ' ') {
    cannon.fire = false;
  }
}

void specialCallback(int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_RIGHT:
      cannon.right = true;
      cannon.time = glutGet(GLUT_ELAPSED_TIME);
      break;
    case GLUT_KEY_LEFT:
      cannon.left = true;
      cannon.time = glutGet(GLUT_ELAPSED_TIME);
      break;
    default:
      return;
  }
}

void specialUpCallback(int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_RIGHT:
      cannon.right = false;
      break;
    case GLUT_KEY_LEFT:
      cannon.left = false;
      break;
    default:
      return;
  }
}

void menuCallBack(int value)
{   
  switch (value) {
    case 0:
      // New game
      initObjectsForNewGame();
      glutIdleFunc(idleCallBack);
      break;
    case 1:
      // Quit
      exit(0);
      break;
    default:
      break;
  }
}

//______________________________________________________________________________
#pragma mark - Menu

void createMenu() {
  menu = glutCreateMenu(menuCallBack);
  glutAddMenuEntry("New game", 0);
  glutAddMenuEntry("Exit", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//______________________________________________________________________________
#pragma mark - Load scene

void loadGameScene()
{
  initObjectsForNewGame();
  
  // Callbacks
  glutDisplayFunc(dispalyCallback);
  glutReshapeFunc(reshapeCallBack);
  glutIdleFunc(idleCallBack);
  glutSpecialFunc(specialCallback);
  glutSpecialUpFunc(specialUpCallback);
  glutKeyboardFunc(keyboardCallback);
  glutKeyboardUpFunc(keyboardUpCallback);
  
  createMenu();
  
  //    Volume of view
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
#ifdef VIEW_3D
  gluPerspective(90, ASPECT_RATIO_WIDTH / ASPECT_RATIO_HEIGHT, 0.1, 2000);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#else
  glOrtho(0, SPACE_WIDTH, 0, SPACE_HEIGHT, -1, 1);
#endif
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
}
