#include "laser.h"
#include "drawUtility.h"
#include "preferences.h"
#include "preferences.h"
#include "collisions.h"
#include <stdlib.h>

// _____________________________________________________________________________
#pragma mark - Declarations

static void shiftLaserVertical(laser_t *laser, GLfloat velocity);

static void collisionLaserTopLine(laser_t *laser);
static void collisionLaserBottomLine(laser_t *laser);
static void collisionLaserBarriers(laser_t *laser, barrier_t barriers[], int numBarriers);
static bool collisionLaserCannon(laser_t *laser, const cannon_t *cannon, game_t *game);
static void collisionLaserAliens(laser_t *laser, aliens_t *aliens, game_t *game);


// _____________________________________________________________________________
#pragma mark - Variables

static const GLfloat SPRITE_LENGTH = 10;
static const GLfloat SPRITE_HEIGHT = 20;
__attribute__((unused)) static const GLfloat SPRITE_DEPTH = 20;

// xMin, xMax, yMin, yMax
static const GLfloat rectangle[4] = {0,  10, 0, 20};

//______________________________________________________________________________
#pragma mark - Init

void initCannonLaser(laser_t *laser, const cannon_t *cannon)
{
  GLfloat h1 = cannon->bb.yMax;
  GLfloat h2 = h1 + SPRITE_HEIGHT;
  GLfloat centerXLaser = (cannon->bb.xMax +  cannon->bb.xMin) / 2;
  
  laser->bb.xMin = centerXLaser - SPRITE_LENGTH / 2;
  laser->bb.xMax = centerXLaser + SPRITE_LENGTH / 2;
  laser->bb.yMin = h1;
  laser->bb.yMax = h2;
  laser->fired = true;
  laser->time = glutGet(GLUT_ELAPSED_TIME);
}

void initAlienLaser(laser_t *laser, const alien_t *alien)
{
  GLfloat h2 = alien->bb.yMin;
  GLfloat h1 = h2 - SPRITE_HEIGHT;
  GLfloat centerXLaser = (alien->bb.xMax +  alien->bb.xMin) / 2;
  
  laser->bb.xMin = centerXLaser - SPRITE_LENGTH / 2;
  laser->bb.xMax = centerXLaser + SPRITE_LENGTH / 2;
  laser->bb.yMin = h1;
  laser->bb.yMax = h2;
  laser->fired = true;
  laser->time = glutGet(GLUT_ELAPSED_TIME);
}

//______________________________________________________________________________
#pragma mark - Update

void shiftLaserVertical(laser_t *laser, GLfloat velocity)
{
  GLfloat now = glutGet(GLUT_ELAPSED_TIME);
  GLfloat space = velocity * (now - laser->time);
  laser->time = now;
  laser->bb.yMin += space;
  laser->bb.yMax += space;
}

void updateCannonLaser(laser_t *cannonLaser, const cannon_t *cannon, 
                       barrier_t *barriers, aliens_t *aliens, game_t *game)
{
  if (!cannonLaser->fired && cannon->fire) {
    initCannonLaser(cannonLaser, cannon);
  }
  
  if (cannonLaser->fired) {
    shiftLaserVertical(cannonLaser, CANNON_LASER_VELOCITY);
  }
  
  collisionLaserTopLine(cannonLaser);
  collisionLaserBarriers(cannonLaser, barriers, BARRIERS_NUM);
  collisionLaserAliens(cannonLaser, aliens, game);
}

bool updateAliensLasers(laser_t aliensLasers[], int *aliensLasersTime, 
                        const aliens_t *aliens, barrier_t barriers[],
                        cannon_t *cannon, game_t *game)
{
  bool lifeLost = false;
  int now = glutGet(GLUT_ELAPSED_TIME);
  
  for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
    if (aliensLasers[i].fired) {
      shiftLaserVertical(&aliensLasers[i], - ALIENS_LASER_VELOCITY);
    }
  }
  
  //     100 ms <= "time" < ALIENS_LASERS_TIME ms
  static int time = ALIENS_LASERS_TIME;
  if (now - *aliensLasersTime > time) {
    do {
      time = rand() % ALIENS_LASERS_TIME;
    } while (time < 100);
    *aliensLasersTime = now;
    for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
      if (!aliensLasers[i].fired) {
        initAlienLaser(&aliensLasers[i], getRandomAlien(aliens));
        break;
      }
    }
  }
  
  for (int i = 0; i < ALIENS_LASERS_NUM; ++i) {
    collisionLaserBottomLine(&aliensLasers[i]);
    collisionLaserBarriers(&aliensLasers[i], barriers, BARRIERS_NUM);
  }
  
  for (int i = 0; i < ALIENS_LASERS_NUM && !lifeLost; ++i) {
    if (collisionLaserCannon(&aliensLasers[i], cannon, game) && game->lives > 0) {
      lifeLost = true;
    }
  }
  return lifeLost;
}

//______________________________________________________________________________
#pragma mark - Draw

void drawLaser(const laser_t *laser)
{
  if (!laser->fired) {
    return;
  }
  
  glPushMatrix();
  glTranslatef(laser->bb.xMin, laser->bb.yMin, 0);
#ifdef VIEW_3D
  glTranslatef(0, 0, -10);
  drawParallelepiped(rectangle[0], rectangle[1],
                     rectangle[2], rectangle[3], SPRITE_DEPTH,
                     MY_COLOR_SKY_1, MY_COLOR_SKY_2, MY_COLOR_SKY_3);
  
  // Reflection
  glTranslatef(0, 0, -80);
  drawParallelepiped(rectangle[0], rectangle[1],
                     rectangle[2], rectangle[3], SPRITE_DEPTH,
                     MY_COLOR_SKY_ALPHA_1, MY_COLOR_SKY_ALPHA_2, MY_COLOR_SKY_ALPHA_3);
#else
  glColor4fv(MY_COLOR_RED_1);
  glBegin(GL_QUADS);
  drawRectangle(rectangle[0], rectangle[1],
                rectangle[2], rectangle[3]);
  glEnd();
#endif
  glPopMatrix();
}

//______________________________________________________________________________
#pragma mark - Collisions

void collisionLaserTopLine(laser_t *laser)
{
  if (laser->fired && laser->bb.yMin > TOP_LINE) {
    laser->fired = false;
  }
}

void collisionLaserBottomLine(laser_t *laser)
{
  if (laser->fired && laser->bb.yMax < BOTTOM_LINE) {
    laser->fired = false;
  }
}

void collisionLaserBarriers(laser_t *laser, barrier_t barriers[], int numBarriers)
{    
  if (laser->fired && laser->bb.yMin < barriers[0].bb.yMax) {
    for (int i = 0; i < numBarriers; ++i) {
      if (barriers[i].life > 0 && isCollision(laser->bb, barriers[i].bb, 0)) {
        laser->fired = false;
        barriers[i].life--;
        break;
      }
    }
  }
}

void collisionLaserAliens(laser_t *laser, aliens_t *aliens, game_t *game)
{
  if (game->state == GAME_STATE_GAME_OVER ||
      !isCollision(laser->bb, aliens->bb, COLLISION_ERROR)) {
    return;
  }
  
  for (int row = aliens->bottomRow; row >= aliens->topRow && laser->fired; --row) {
    for (int col = aliens->leftCol; col <= aliens->rightCol; ++col) {
      
      alien_t *alienTMP = &aliens->matrix[row][col];
      if (alienTMP->life == ALIEN_LIFE_ALIVE && isCollision(laser->bb, alienTMP->bb, COLLISION_ERROR)) {
        
        // If there's an alien on a bottom line don't manage collision
        for (int i = row + 1; i < ALIENS_ROWS; ++i) {
          if (aliens->matrix[i][col].life == ALIEN_LIFE_ALIVE) {
            return;
          }
        }
        
        laser->fired = false;
        alienTMP->life = ALIEN_LIFE_FIRED;
        alienTMP->timeFired =  glutGet(GLUT_ELAPSED_TIME);
        aliens->killed++;
        game->score += getPoints(alienTMP);
        if (aliens->killed == ALIENS_NUM) {
          game->state = GAME_STATE_WIN;
          return;
        }
        if (alienTMP->bb.xMax > aliens->bb.xMax - 30) {
          updateAliensBBxMax(aliens);  //
        } else if (alienTMP->bb.xMin < aliens->bb.xMin + 30) {
          updateAliensBBxMin(aliens);
        }
        
        if (alienTMP->bb.yMax == aliens->bb.yMax) {
          updatedAliensBByMax(aliens);
        } else if (alienTMP->bb.yMin == aliens->bb.yMin) {
          updatedAliensBByMin(aliens);
        }
        break;
      }
    }
  }
}

bool collisionLaserCannon(laser_t *laser, const cannon_t *cannon, game_t *game)
{
  if (game->state == GAME_STATE_GAME_OVER) {
    return false;
  }
  
  if (laser->fired && isCollision(laser->bb, cannon->bb, 0)) {
    laser->fired = false;
    game->lives -= 1;
    if (game->lives == 0) {
      game->state = GAME_STATE_GAME_OVER;
    }
    return true;
  }
  return false;
}
