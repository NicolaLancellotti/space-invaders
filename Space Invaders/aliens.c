#include "aliens.h"
#include <stdbool.h>
#include <stdlib.h>
#include "glutCrossPlatform.h"
#include "preferences.h"
#include "collisions.h"

// _____________________________________________________________________________
#pragma mark - Declarations

static void moveAliens(aliens_t *aliens, GLfloat maxVelocity, GLfloat minVelocity, 
                       GLfloat verticalShift, GLfloat width);
static void shiftAliensHorizontal(aliens_t *aliens, GLfloat shift);
static void shiftAliensVertical(aliens_t *aliens, GLfloat shift);

static void collisionAliensBarriers(const aliens_t *aliens, barrier_t barriers[], int numBarriers);
static bool collisionAliensCannon(const aliens_t *aliens, const cannon_t *cannon, game_t *game);
static void collisionAliensBottomLine(const aliens_t *aliens, game_t *game);

// _____________________________________________________________________________
#pragma mark - Variables

const int ALIENS_NUM = ALIENS_COL * ALIENS_ROWS;

// _____________________________________________________________________________
#pragma mark - Init

void initAliens(aliens_t *aliens)
{
  aliens->rightCol = ALIENS_COL - 1;
  aliens->leftCol = 0;
  aliens->bottomRow = ALIENS_ROWS - 1;
  aliens->topRow = 0;
  
  aliens->bb.xMax = aliens->matrix[ALIENS_ROWS - 1][aliens->rightCol].bb.xMax;
  aliens->bb.xMin = aliens->matrix[ALIENS_ROWS - 1][aliens->leftCol].bb.xMin;
  
  aliens->bb.yMax = aliens->matrix[aliens->topRow][0].bb.yMax;
  aliens->bb.yMin = aliens->matrix[aliens->bottomRow][0].bb.yMin;
  
  aliens->rightDirection = true;
  aliens->killed = 0;
  aliens->time = glutGet(GLUT_ELAPSED_TIME);
}

// _____________________________________________________________________________
#pragma mark - Update

bool updateAliens(aliens_t *aliens, cannon_t *cannon, barrier_t barriers[], game_t *game)
{
  bool lifeLost = false;
  int now = glutGet(GLUT_ELAPSED_TIME);
  if (now - aliens->time > ALIENS_TIME) {
    moveAliens(aliens, ALIENS_MAX_VELOCITY, ALIENS_MIN_VELOCITY, ALIENS_VERTICAL_SHIFT, SPACE_WIDTH);
    
  }
  
  killAliens(aliens);
  
  collisionAliensBarriers(aliens, barriers, BARRIERS_NUM);
  
  collisionAliensBottomLine(aliens, game);
  
  if (collisionAliensCannon(aliens, cannon, game) && game->lives > 0) {
    lifeLost = true;
  }
  
  return lifeLost;
}

void moveAliens(aliens_t *aliens, GLfloat maxVelocity, GLfloat minVelocity, 
                GLfloat verticalShift, GLfloat width)
{
  GLfloat now = glutGet(GLUT_ELAPSED_TIME);
  GLfloat velocity = (maxVelocity - minVelocity) *
  ((float)aliens->killed/ALIENS_NUM) + minVelocity;
  GLfloat space = velocity * (now - aliens->time);
  aliens->time = now;
  
  if (aliens->rightDirection) {
    if (aliens->bb.xMax + space < width) {
      shiftAliensHorizontal(aliens, space);
    } else {
      shiftAliensVertical(aliens, verticalShift);
      aliens->rightDirection = false;
    }
  } else {
    if (aliens->bb.xMin - space > 0) {
      shiftAliensHorizontal(aliens, -space);
    } else {
      shiftAliensVertical(aliens, verticalShift);
      aliens->rightDirection = true;
    }
  }
}

void shiftAliensHorizontal(aliens_t *aliens, GLfloat shift)
{
  aliens->bb.xMax += shift;
  aliens->bb.xMin += shift;
  for (int row = 0; row < ALIENS_ROWS; ++row) {
    for (int col = 0; col < ALIENS_COL; ++col) {
      aliens->matrix[row][col].bb.xMin += shift;
      aliens->matrix[row][col].bb.xMax += shift;
      nextStateAlien(&aliens->matrix[row][col]);
    }
  }
}

void shiftAliensVertical(aliens_t *aliens, GLfloat shift)
{
  aliens->bb.yMax += shift;
  aliens->bb.yMin += shift;
  for (int row = 0; row < ALIENS_ROWS; ++row) {
    for (int col = 0; col < ALIENS_COL; ++col) {
      aliens->matrix[row][col].bb.yMin += shift;
      aliens->matrix[row][col].bb.yMax += shift;
    }
  }
}

// _____________________________________________________________________________
#pragma mark - Update bounding box

void updateAliensBBxMax(aliens_t *aliens)
{
  for (int row = ALIENS_ROWS - 1; row >= 0; --row) {
    if (aliens->matrix[row][aliens->rightCol].life == ALIEN_LIFE_ALIVE) {
      return;
    }
  }
  aliens->rightCol--;
  aliens->bb.xMax = aliens->matrix[0][aliens->rightCol].bb.xMax;
  updateAliensBBxMax(aliens);
}

void updateAliensBBxMin(aliens_t *aliens)
{
  for (int row = ALIENS_ROWS - 1; row >= 0; --row) {
    if (aliens->matrix[row][aliens->leftCol].life == ALIEN_LIFE_ALIVE) {
      return;
    }
  }
  aliens->leftCol++;
  aliens->bb.xMin = aliens->matrix[0][aliens->leftCol].bb.xMin;
  updateAliensBBxMin(aliens);
}

void updatedAliensBByMax(aliens_t *aliens)
{
  for (int col = ALIENS_COL - 1; col >= 0; --col) {
    if (aliens->matrix[aliens->topRow][col].life == ALIEN_LIFE_ALIVE) {
      return;
    }
  }
  aliens->topRow++;
  aliens->bb.yMax = aliens->matrix[aliens->topRow][0].bb.yMax;
  updatedAliensBByMax(aliens);
}

void updatedAliensBByMin(aliens_t *aliens)
{
  for (int col = ALIENS_COL - 1; col >= 0; --col) {
    if (aliens->matrix[aliens->bottomRow][col].life == ALIEN_LIFE_ALIVE) {
      return;
    }
  }
  aliens->bottomRow--;
  aliens->bb.yMin = aliens->matrix[aliens->bottomRow][0].bb.yMin;
  updatedAliensBByMin(aliens);
}

// _____________________________________________________________________________
#pragma mark - Draw

void drawAliens(const aliens_t *aliens)
{
  for (int row = 0; row < ALIENS_ROWS; ++row) {
    for (int col = 0; col < ALIENS_COL; ++col) {
      const alien_t *alienTmp = &aliens->matrix[row][col];
      if (alienTmp->life == ALIEN_LIFE_DEAD) {
        continue;
      }
      drawAlien(alienTmp);
    }
  }
}

// _____________________________________________________________________________
#pragma mark - Other

const alien_t* getRandomAlien(const aliens_t *aliens)
{
  if (aliens->killed == ALIENS_NUM) {
    return NULL;
  }
  while (1) {
    int col = rand() % ALIENS_COL;
    for (int row = aliens->bottomRow; row >= aliens->topRow; --row) {
      if (aliens->matrix[row][col].life == ALIEN_LIFE_ALIVE) {
        return &aliens->matrix[row][col];
      }
    }
  }
}

void killAliens(aliens_t *aliens)
{
  int now = glutGet(GLUT_ELAPSED_TIME);
  for (int row = 0; row < ALIENS_ROWS; ++row) {
    for (int col = 0; col < ALIENS_COL; ++col) {
      alien_t *alienTmp = (alien_t *)&aliens->matrix[row][col];
      if (alienTmp->life == ALIEN_LIFE_FIRED &&
          now - alienTmp->timeFired > ALIENS_TIME_BEWTWEEN_FIRED_KILL) {
        alienTmp->life = ALIEN_LIFE_DEAD;
      }
    }
  }
}

//______________________________________________________________________________
#pragma mark - Collisions

void collisionAliensBarrier(const aliens_t *aliens, barrier_t *barrier)
{
  for (int row = aliens->bottomRow; row >= aliens->topRow; --row) {
    for (int col = aliens->leftCol; col <= aliens->rightCol; ++col) {
      const alien_t *alienTMP = &aliens->matrix[row][col];
      if (alienTMP->life == ALIEN_LIFE_ALIVE && isCollision(barrier->bb, alienTMP->bb, 0)) {
        barrier->life = 0;
        return;
      }
    }
  }
}

void collisionAliensBarriers(const aliens_t *aliens, barrier_t barriers[], int barriersNum)
{
  for (int i = 0; i < barriersNum; ++i) {
    barrier_t *barrierTMP = &barriers[i];
    if (barrierTMP->life > 0 && isCollision(barrierTMP->bb, aliens->bb, 0)) {
      collisionAliensBarrier(aliens, barrierTMP);
    } else {
      continue;
    }
  }
}

bool collisionAliensCannon(const aliens_t *aliens, const cannon_t *cannon, game_t *game)
{
  if (game->state == GAME_STATE_GAME_OVER) {
    return false;
  }
  
  if (!isCollision(cannon->bb, aliens->bb, 0)) {
    return false;
  }
  for (int row = aliens->bottomRow; row >= aliens->topRow; --row) {
    for (int col = aliens->leftCol; col <= aliens->rightCol; ++col) {
      const alien_t *alienTMP = &aliens->matrix[row][col];
      if (alienTMP->life == ALIEN_LIFE_ALIVE && isCollision(cannon->bb, alienTMP->bb, 0)) {
        game->lives -= 1;
        if (game->lives == 0) {
          game->state = GAME_STATE_GAME_OVER;
        }
        return true;
      }
    }
  }
  return false;
}

void collisionAliensBottomLine(const aliens_t *aliens, game_t *game)
{
  if (aliens->bb.yMin < BOTTOM_LINE) {
    game->state = GAME_STATE_GAME_OVER;
  }
}
