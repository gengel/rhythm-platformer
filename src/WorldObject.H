#ifndef WORLDOBJ_H
#define WORLDOBJ_H

#include <iostream>
#include <vector>
#include "Sprite.H"
#include "Sound.H"

#define MAX_STATES 20
#define ACCEL_RATE 0.0002
#define VELOC_LOSS 0.8

using namespace std;

enum states_generic { FLOAT = 0, 
		      UP_LEFT, UP, UP_RIGHT, RIGHT,
		      DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT,
		      DEAD };

class WorldObject
{
 public:


  /* Generic Constructor

     "states[20]" is an array of sprite pointers
     This is used so that when someone calls "setState"
     with a num (probably enum'd by a subclass) the
     correct Sprite shall be set as the current

     About the other units:
     width, height, Xpos, Ypos are in pixels

     Xvel, Yvel are in pixels/nanosecond * ACCEL_RATE

     Xacc, Yacc are in pixels/nanosecond^2

  */
 
  WorldObject(Sprite* states[MAX_STATES],
	      unsigned long int width = 1,
	      unsigned long int height = 1,
	      signed long int xMax = 1,
	      signed long int yMax = 1,
	      double Xpos = 0,
	      double Ypos = 0,
	      double Xvel = 0,
	      double Yvel = 0,
	      double Xacc = 0,
	      double Yacc = 0,
	      unsigned long int curr = FLOAT,
	      double mass = 1) 
  {
    myWidth = width;
    myHeight = height;
    myXpos = Xpos;
    myYpos = Ypos;
    myXvel = Xvel;
    myYvel = Yvel;
    myXaccel = Xacc;
    myYaccel = Yacc;
    
    myXmax = xMax - myWidth;
    myYmax = yMax - myHeight;

    currentSprite = curr;

    myMass = mass;

    crash = NULL;

    for(int i =0; i < MAX_STATES; i++)
      this->states[i] = states[i];

    //cerr << "myXmax: " << myXmax << endl;
    //cerr << "myYmax: " << myYmax << endl;

  }


  inline double getPositionX()     { return myXpos; }
  inline double getPositionY()     { return myYpos; }
  inline double getVelocityX()     { return myXvel; }
  inline double getVelocityY()     { return myYvel; }
  inline double getAccelerationX() { return myXaccel; }
  inline double getAccelerationY() { return myYaccel; }
  inline int    getHeight()        { return myHeight; }
  inline int    getWidth()         { return myWidth; }


  //calculate new position, in ideal world
  virtual void update(long elapsedTime);
  //use values from update() as new values
  virtual void ok();
  // manual adjustment of accel, vel, pos in event of collision
  virtual void adjust(double Xaccel, double Yaccel,
		      double Xvel,   double Yvel,
		      double Xpos,   double Ypos,
		      double newX,   double newY);
  

  virtual Sprite* getCurrentSprite();

  virtual void setState(states_generic newState);
  virtual unsigned int getState();

  virtual void draw(SDL_Surface* dest);
  virtual void erase();

  inline void setCrash(Sound* cr) { crash = cr; }

 protected:

  double myXaccel;
  double myYaccel;

  double myXvel;
  double myYvel;
 
  double myXpos;
  double myYpos;

  // used between update() and ok()
  double newXpos;
  double newYpos;
  
  signed long int myXmax;
  signed long int myYmax;

  unsigned long int myHeight;
  unsigned long int myWidth;

  Sprite* states[MAX_STATES];
  unsigned int currentSprite;

  Sound* crash;

  double myMass;

  //unsigned long int lastTime;

};


#endif
