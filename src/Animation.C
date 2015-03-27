#include "Animation.H"

Animation::Animation(SDL_Surface* imgs[MAX_FRAMES],
		     int delays[MAX_FRAMES], 
		     int numFrames,
		     int height, int width,
		     int offset)
{
  for(int i = 0; i < numFrames && i < MAX_FRAMES; i++)
    {
      myImgs[i] = imgs[i];
      myDelays[i] = delays[i];
    }

  myFrames = ( numFrames < MAX_FRAMES ? numFrames : MAX_FRAMES - 1);
  myHeight = height;
  myWidth = width;
  myOffset = offset;
}


int Animation::getTotalTime()
{
  int total = 0;
  for(int i = 0; i < myFrames; i++)
    total += myDelays[i];

  return total;

}


void Animation::update(long elapsedTime)
{
  lastTime += elapsedTime;
  int total = getTotalTime();

  if(lastTime >= total)
    lastTime = lastTime % total;

}

SDL_Surface* Animation::current()
{
  int sum = 0;
  for(int i = 0; i < myFrames; i++)
    {
      sum += myDelays[i];
      if(lastTime < sum)
	return myImgs[i];
    }

  //return last frame
  return myImgs[myFrames - 1];
}
