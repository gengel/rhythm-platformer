#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Animation.H"
#include "PlatformerException.H"

using namespace std;

class Sprite
{
 public:

  // constructs from file
  Sprite(char* PNG_filename);

  // constructs from SDL_surface pointer
  Sprite(SDL_Surface* image);

  // constructs from Animation object
  // (will draw based on Animation's current frame)
  Sprite(Animation* animation);

  // draw to dest at (x,y)
  void draw(SDL_Surface* dest, 
	    int x = 0, int y = 0);

  void erase();

  inline int getHeight() { return myHeight; }
  inline int getWidth() { return myWidth; }

  void update(long elapsedTime);

  inline void setName(char* n)  { name = n; } 

 private:

  int myHeight;
  int myWidth;

  SDL_Surface* myLast;
  int myLastX;
  int myLastY;

  // true if an animation, otherwise false
  bool anim;

  SDL_Surface* myImg;
  Animation*   myAnim;

  char*        name;

  


};

#endif
  

  
  
