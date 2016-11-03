#include "game.h"
#include "drawUtility.h"
#include "preferences.h"
#include "glutCrossPlatform.h"
#include "printWords.h"

//______________________________________________________________________________
#pragma mark - Init

void initGame(game_t *game)
{
  game->score = 0;
  game->lives = 2;
}

//______________________________________________________________________________
#pragma mark - Draw

//  draw heads-up display
void drawHUD(const game_t *game)
{
#ifdef VIEW_3D
  glColor3fv(MY_COLOR_ORANGE_3);
  printWords(-30, 85, -100, "SPACE INVADERS");
  glColor3fv(MY_COLOR_VIOLET_1);
  printWords(-115, -70, -100, "LIVES %d", game->lives);
  printWords(-115, -80, -100, "SCORE %d", game->score);
  
  switch (game->state) {
    case GAME_STATE_GAME_OVER:
      glColor3fv(MY_COLOR_RED_3);
      printWords(-115, -55, -100, "GAME OVER");
      break;
    case GAME_STATE_PAUSE:
      glColor3fv(MY_COLOR_ORANGE_3);
      printWords(-115, -55, -100, "PAUSE");
      break;
    default:
      glColor3f(0.0, 1.0, 0.0);
      glColor3fv(MY_COLOR_GREEN_2);
      printWords(-115, -55, -100, "PLAY");
  }
#else
  glColor3fv(MY_COLOR_GREEN_1);
  printWords(30, SPACE_HEIGHT - 80, 0, "SCORE %d", game->score);
  printWords(SPACE_WIDTH - 225, SPACE_HEIGHT - 80, 0, "LIVES %d", game->lives);
  
  switch (game->state) {
    case GAME_STATE_GAME_OVER:
      glColor3fv(MY_COLOR_ORANGE_1);
      printWords(SPACE_WIDTH / 2 - 100, SPACE_HEIGHT - 80, 0, "GAME OVER");
      break;
    case GAME_STATE_PAUSE:
      glColor3fv(MY_COLOR_YELLOW_1);
      printWords(SPACE_WIDTH / 2 - 50, SPACE_HEIGHT - 80, 0, "PAUSE");
      break;
    default:
      glColor3fv(MY_COLOR_GREEN_1);
      printWords(SPACE_WIDTH / 2 - 50, SPACE_HEIGHT - 80, 0, "PLAY");
  }
#endif
}
