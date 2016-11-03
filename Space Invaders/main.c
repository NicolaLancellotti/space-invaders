#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "glutCrossPlatform.h"
#include "preferences.h"
#include "gameScene.h"

int main(int argc, char *argv[]) 
{
  srand((unsigned)time(NULL));
  
  //______________________________________________________________________________
  //          GLUT
  
  glutInit(&argc, argv);
#ifdef Z_BUFFER
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
#else
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
#endif    
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow(WINDOW_TITLE);
  
  //______________________________________________________________________________
  //          OpenGL
  
  glClearColor(0, 0, 0, 1.0);
  
#ifdef Z_BUFFER
  glEnable(GL_DEPTH_TEST);
#endif
  
#ifdef BACK_FACE_CULLING
  glEnable(GL_CULL_FACE);
#endif
  
  //______________________________________________________________________________
  //          Start game
  
  loadGameScene();
  glutMainLoop();
  return 0;
}
