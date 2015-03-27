#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_audio.h>

#include "Sound.H"
#include "Sprite.H"
#include "WorldObject.H"
#include "CircleObject.H"

#define BLACK 0x000000

#define WIDTH 800
#define HEIGHT 600

using namespace std;


/* Unnamed Physics Demo
   1/28/2005
   gengel@cs.oberlin.edu

   Using some laws of momentum from physics, 
   we allow a player to move around and
   bounce stuff.

   Demonstrates use of SDL Video, Audio, 
   and Input

*/




int main()
{
  if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
    cerr << "Unable to init SDL for some reason." << endl;
    exit(-1);
  }


  /* Initialize Audio */
  /* Borrowed from SDL Tutorial on SDL's Website */
  //extern void mixaudio(void *unused, Uint8 *stream, int len);
  //SDL_AudioSpec fmt;
  
  /* Set 16-bit stereo audio at 22Khz */
//   fmt.freq = 22050;
//   fmt.format = AUDIO_S16;
//   fmt.channels = 2;
//   fmt.samples = 512;        /* A good value for games */
//   fmt.callback = mixaudio;
//   fmt.userdata = NULL;

  /* Open the audio device and start playing sound! */
  //  if ( SDL_OpenAudio(&fmt, NULL) < 0 ) {
  //fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
  //exit(1);
  //}



  /* Initialize Audio */
  // borrowed from SDL_Mixer Tutorial
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; 
  int audio_channels = 2;
  int audio_buffers = 4096;

  
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  }






  /* Initialize Video */
  /* Also borrowed from SDL */

  SDL_Surface *screen = SDL_GetVideoSurface();
  //SDL_Surface *current;

  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, 
			    SDL_SWSURFACE | 
			    SDL_DOUBLEBUF);


  if(screen == NULL) {
    cerr << "Unable to set " << WIDTH 
	 << "x" << HEIGHT << "!" << endl;
    exit(-1);
  }




  // Everything ok? Now begin loading stuff!


  try {

    //SDL_PauseAudio(0);

    Sound boing("boing_x.wav");
    //boing.playNow();
    //boing.stopNow();

    Sprite test("grah.png");
    Sprite blah("grr.png");
    Sprite bigg("big.png");
    Sprite pea("pea.png");

    Sprite* states[20];
    Sprite* os[20];
    Sprite* big[20];
    Sprite* peas[20];
    
    for(int i = 0; i < 20; i++)
      {
	states[i] = &test;
	os[i] = &blah;
	big[i] = &bigg;
	peas[i] = &pea;
      }
    
    
    states[FLOAT] = new Sprite("face-FLOAT.png");
    states[UP_LEFT] = new Sprite("face-UPLEFT.png");
    states[UP] = new Sprite("face-UP.png");
    states[UP_RIGHT] = new Sprite("face-UPRIGHT.png");
    states[RIGHT] = new Sprite("face-RIGHT.png");
    states[DOWN_RIGHT] = new Sprite("face-DOWNRIGHT.png");
    states[DOWN_LEFT] = new Sprite("face-DOWNLEFT.png");
    states[DOWN] = new Sprite("face-DOWN.png");
    states[LEFT] = new Sprite("face-LEFT.png");


    CircleObject dude(states, 65, 65, 65, WIDTH, HEIGHT,
		      0, 0, 0, 0, FLOAT, 
		      10);

    dude.setCrash(&boing);

    CircleObject guy(os, 65, 250, 250, WIDTH, HEIGHT,
		     0,0,0,0, FLOAT,
		     2);

    guy.setCrash(&boing);

    CircleObject moon(big, 150, 450,400, WIDTH, HEIGHT,
		      0, 0, 0, 0,  FLOAT, 
		      20);

    moon.setCrash(&boing);

    

    const int CIRCS = 6;

    CircleObject* allCircs[CIRCS];
    allCircs[0] = &dude;
    allCircs[1] = &guy;
    allCircs[2] = &moon;

      //add in some peas!
    for(int i = 3; i < CIRCS; i++)
     {
    	allCircs[i] = 
	  new CircleObject(peas, 15, (i * 45) + 200, 
			   20, WIDTH, HEIGHT,
			   -0.2, 0.2, 0, 0, FLOAT, 5);
      }
    			       
    		       
				     
		     


    SDL_Event event;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    unsigned long int now = SDL_GetTicks();
    unsigned long int last = SDL_GetTicks();
    unsigned long int elapsed = 0;

    while(true)
      {

	/* Update All Objects And Do Collisions */

	now = SDL_GetTicks();
	elapsed = now - last;
	last = now;

	for(int i = 0; i < CIRCS; i++)
	  allCircs[i]->update(elapsed);

	for(int i = 0; i < CIRCS; i++)
	  for(int j = i + 1; j < CIRCS; j++)
	    allCircs[i]->doCollision(*(allCircs[j]));
	
	for(int i = 0; i < CIRCS; i++)
	  allCircs[i]->ok();



	/* Check for Input... */

	while ( SDL_PollEvent(&event) ) {
	  switch (event.type) {
  	  case SDL_KEYDOWN:
	    switch( event.key.keysym.sym ) {
	    case SDLK_LEFT:
	      left = true;
	      break;
	    case SDLK_RIGHT:
	      right = true;
	      break;
	    case SDLK_UP:
	      up = true;
	      break;
	    case SDLK_DOWN:
	      down = true;
	      break;
	    case SDLK_ESCAPE:
	      exit(0);
	      break;
	    default:
	      break;
	    }
	    break;
	    
	  case SDL_KEYUP:
	    switch(event.key.keysym.sym) {
	    case SDLK_LEFT:
	      if(left)
		left = false;
	      break;

	    case SDLK_RIGHT:
	      if(right)
		right = false;
	      break;

	    case SDLK_UP:
	      if(up)
		up = false;
	      break;
	    case SDLK_DOWN:
	      if(down)
		down = false;
	      break;
	    default:
	      break;
	    }

	  }
	  
	}

	/* ...and Adjust Player State */

	if(left && !right) {
	  if(up && !down) {
	    dude.setState(UP_LEFT);
	  } else if(down && !up) {
	    dude.setState(DOWN_LEFT);
	  } else {
	    dude.setState(LEFT);
	  }
	} else if(right && !left) {
	  if(up && !down) {
	    dude.setState(UP_RIGHT);
	  } else if (down && !up) {
	    dude.setState(DOWN_RIGHT);
	  } else {
	    dude.setState(RIGHT);
	  }
	} else {
	  if(up && !down) {
	    dude.setState(UP);
	  } else if(down && !up) {
	    dude.setState(DOWN);
	  } else {
	    dude.setState(FLOAT);
	  }
	}
	  



	/* Refresh the Screen */

	SDL_FillRect(screen, NULL, BLACK);
	
	/* "Erasing" isn't actually necessary here,
	   but if I weren't using SDL_Flip and double-
	   buffering, I'd want it; in any case, 
	   leave the call in, since the actual method
	   body is current commented out
	*/
	for(int i = 0; i < CIRCS; i++)
	  allCircs[i]->erase();

	for(int i = 0; i < CIRCS; i++)
	  allCircs[i]->draw(screen);

	SDL_Flip(screen);

	//since we're running in software mode,
	//give the system some time to do stuff
	// (Will lower framerate slightly, 
	//  but really, who cares)
	SDL_Delay(10);
      }

    
    
    for(int i = 3; i < CIRCS; i++)
      delete allCircs[i]; 
    

  
  }
  catch (exception e) {
    cerr << "Exception!" << endl;
    cout << e.what() << endl;
    atexit(SDL_Quit);
  }

  /*  //dumb delay
  for(int i = 0; i < 1990000; i++)
    { cout << "poop\n"; }
  */


  //Close Audio
  //SDL_CloseAudio();
  Mix_CloseAudio();


  atexit(SDL_Quit);

  return 0;
}



