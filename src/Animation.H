#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SDL/SDL.h>

#include "PlatformerException.H"

#define MAX_FRAMES 20

using namespace std;

class Animation
{
 public:
  
  // needs array of image pointers,
  // plus array of 'time to delay' for each
  // in nanoseconds
  // also, height, width
  Animation(SDL_Surface* imgs[MAX_FRAMES],
	    int delays[MAX_FRAMES], int numFrames,
	    int height, int width,
	    int offset = 0);

  SDL_Surface* current();

  inline int getHeight() { return myHeight; }
  inline int getWidth() { return myWidth; }

  void update(long elapsedTime);

  int getTotalTime();

private:

  SDL_Surface* myImgs[MAX_FRAMES];
  int          myDelays[MAX_FRAMES];

  int myHeight;
  int myWidth;
  int myOffset;
  int myFrames;

  long lastTime;

};

  





#endif
