#ifndef __Space_Invaders__laser__
#define __Space_Invaders__laser__

#include <stdio.h>
#include <stdbool.h>
#include "glutCrossPlatform.h"
#include "cannon.h"
#include "alien.h"
#include "barrier.h"
#include "aliens.h"
#include "game.h"

typedef struct {
  boundingBox_t bb;
  bool fired;
  int time; // The movement is a function of time
} laser_t;


//______________________________________________________________________________
#pragma mark - Init

void initCannonLaser(laser_t *laser, const cannon_t *cannon);
void initAlienLaser(laser_t *alienLaser, const alien_t *alien);

//______________________________________________________________________________
#pragma mark - Update

bool updateAliensLasers(laser_t aliensLasers[], int *aliensLasersTime, 
                        const aliens_t *aliens, barrier_t barriers[],
                        cannon_t *cannon, game_t *game);

void updateCannonLaser(laser_t *cannonLaser, const cannon_t *cannon, 
                       barrier_t *barriers, aliens_t *aliens, game_t *game);
//______________________________________________________________________________
#pragma mark - Draw

void drawLaser(const laser_t *laser);


#endif /* defined(__Space_Invaders__laser__) */
