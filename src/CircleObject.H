#ifndef CIRCLEOBJ_H
#define CIRCLEOBJ_H

#include "WorldObject.H"


#define PI 3.14159

class CircleObject : public WorldObject
{
  

 public:
  
  

  /* Xpos and Ypos can be determined from center and radius
     
     The rest can be passed on to the WorldObject constructor
  */

  CircleObject(Sprite* states[MAX_STATES],
	       double radius = 1, 
	       double centerX = 0,
	       double centerY = 0,
	       signed long int xMax = 1,
	       signed long int yMax = 1,
	       double Xvel = 0,
	       double Yvel = 0,
	       double Xacc = 0,
	       double Yacc = 0,
	       unsigned long int curr = FLOAT,
	       double dens = 1);

  inline double getRadius()  { return myRadius; }
  inline double getCenterX() { return myXpos + myRadius; }
  inline double getCenterY() { return myYpos + myRadius; }

  inline double getNewCenterX() { return newXpos + myRadius; }
  inline double getNewCenterY() { return newYpos + myRadius; }

  virtual bool checkCollision(CircleObject& other);
  virtual void doCollision(CircleObject& other);

  virtual void ok();

 protected:

  double myRadius;

  //bool justCollided;
  
};
  
#endif
