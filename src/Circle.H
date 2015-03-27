#ifndef CIRCLEOBJ_H
#define CIRCLEOBJ_H

#include "WorldObject.H"

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
	       unsigned long int curr = FLOAT);

  inline double getRadius() { return myRadius; }
  inline double getCenterX() { return (myXpos + (myWidth/2)); }
  inline double getCenterY() { return (myYpos + (myHeight/2)); }

  virtual void update(long elapsedTime);

 protected:

  double myRadius;

}
  
#endif
