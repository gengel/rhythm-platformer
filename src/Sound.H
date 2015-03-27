#ifndef SOUND_H
#define SOUND_H

#define NUM_SOUNDS 2

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>


/* Basic Class that loads a sound file,
   then plays on command.

   Modified from the PlaySound function in 
   SDL's tutorial

   --gengel 2/11/05
*/


class Sound
{

public:
  Sound(char* file);
  void playNow();
  void stopNow();
  void play();


private:
  /*
  int index;
  SDL_AudioSpec wave;
  Uint8   *data;
  Uint32   dlen;
  SDL_AudioCVT cvt;
  */

  Mix_Chunk* mySound;
  int myChannel;
};





#endif
