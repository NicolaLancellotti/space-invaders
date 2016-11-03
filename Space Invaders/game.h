//
//  game.h
//  Space Invaders
//
//  Created by Nicola Lancellotti on 4/3/15.
//  Copyright (c) 2015 Nicola Lancellotti. All rights reserved.
//

#ifndef __Space_Invaders__game__
#define __Space_Invaders__game__

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    GAME_STATE_PLAY,
    GAME_STATE_GAME_OVER,
    GAME_STATE_WIN,
    GAME_STATE_PAUSE
} gameState_t;

typedef struct {
    int score;
    int lives;
    gameState_t state;
} game_t;

//______________________________________________________________________________
#pragma mark - Init

void initGame(game_t *game);

//______________________________________________________________________________
#pragma mark - Draw

void drawHUD(const game_t *game);

#endif /* defined(__Space_Invaders__game__) */
