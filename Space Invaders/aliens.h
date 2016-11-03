#ifndef __Space_Invaders__aliens__
#define __Space_Invaders__aliens__

#include <stdio.h>
#include <stdbool.h>
#include "boundingBox.h"
#include "alien.h"
#include "preferences.h"
#include "game.h"
#include "barrier.h"
#include "cannon.h"

extern const int ALIENS_NUM;

typedef struct {
  alien_t matrix[ALIENS_ROWS][ALIENS_COL];
  boundingBox_t bb;
  int rightCol;        // rightmost column in which there are aliens
  int leftCol;         // leftmost column in which there are aliens
  int bottomRow;       // The lowest line in which there are aliens
  int topRow;          // Top line where there are aliens
  bool rightDirection;
  int time;            // Last time the aliens have moved
  int killed;
} aliens_t;

//______________________________________________________________________________
#pragma mark - Init

// This function must be invoked after void initAlien(alien_t *, GLfloat, GLfloat, alienType_t)
void initAliens(aliens_t *aliens); 

//______________________________________________________________________________
#pragma mark - Update

bool updateAliens(aliens_t *aliens, cannon_t *cannon, barrier_t barriers[], game_t *game);

//______________________________________________________________________________
#pragma mark - Update bounding box

void updateAliensBBxMax(aliens_t *aliens);
void updateAliensBBxMin(aliens_t *aliens);
void updatedAliensBByMax(aliens_t *aliens);
void updatedAliensBByMin(aliens_t *aliens);

//______________________________________________________________________________
#pragma mark - Draw

void drawAliens(const aliens_t *aliens);

//______________________________________________________________________________
#pragma mark - Other

void killAliens(aliens_t *aliens);
const alien_t* getRandomAlien(const aliens_t *aliens);

#endif /* defined(__Space_Invaders__aliens__) */
