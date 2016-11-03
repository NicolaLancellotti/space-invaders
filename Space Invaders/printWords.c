#include "printWords.h"
#include <stdarg.h>
#include <stdlib.h>
#include "glutCrossPlatform.h"

static void *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

void printWords(float x, float y, float z, const char* format, ...)
{
  
  va_list args;	//  Variable argument list
  int len;		//	String length
  int i;			//  Iterator
  char * text;	//	Text
  
  //  Initialize a variable argument list
  va_start(args, format);
  
  //  Return the number of characters in the string referenced the list of arguments.
  //  _vscprintf doesn't count terminating '\0' (that's why +1)
  
#ifdef WIN32
  len = _vscprintf(format, args) + 1;
  //  Allocate memory for a string of the specified size
  text = (char *)malloc(len * sizeof(char));
  //  Write formatted output using a pointer to the list of arguments
  vsprintf_s(text, len, format, args);
#else
  len = 50;
  //  Allocate memory for a string of the specified size
  text = (char *)malloc(len * sizeof(char));
  //  Write formatted output using a pointer to the list of arguments
  vsprintf(text, format, args);
#endif
  
  //  End using variable argument list
  va_end(args);
  
  //  Specify the raster position for pixel operations.
  glRasterPos3f(x, y, z);
  
  //  Draw the characters one by one
  for (i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(font_style, text[i]);
  
  //  Free the allocated memory for the string
  free(text);
}
