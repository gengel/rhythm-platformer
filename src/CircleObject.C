#include "CircleObject.H"
#include <math.h>


//bool CircleObject::WARNING = false;

CircleObject::CircleObject(Sprite* states[MAX_STATES],
	       double radius, 
	       double centerX,
	       double centerY,
	       signed long int xMax,
	       signed long int yMax ,
	       double Xvel ,
	       double Yvel ,
	       double Xacc ,
	       double Yacc ,
	       unsigned long int curr,
	       double dens) 

  : WorldObject(states, (int)(radius*2), (int)(radius*2), 
		xMax, yMax,
		(centerX - radius), (centerY - radius),
		Xvel, Yvel, Xacc, Yacc, curr, 
		(dens*PI*radius*radius))
  { 
    myRadius = radius;
    //justCollided = false;
    //   myCenterX = centerX;
    //myCenterY = centerY;

  }


void CircleObject::ok()
{
  WorldObject::ok();

  /* 
  myCenterX = myXpos + (myRadius/2);
  myCenterY = myYpos + (myRadius/2);
  */
}



bool CircleObject::checkCollision(CircleObject& other)
{
  
  double dx = getNewCenterX() - other.getNewCenterX();
  double dy = getNewCenterY() - other.getNewCenterY();

  //printf("x distance,%f",dx);

  double minDist = myRadius + other.myRadius;

  return( (dx*dx + dy*dy) < (minDist*minDist));

}




void CircleObject::doCollision(CircleObject& other)
{
  if(checkCollision(other))
    {
 
      // Find normal from other to me

      double normX = getCenterX() - other.getCenterX();
      double normY = getCenterY() - other.getCenterY();

      // make into unit vector

      double normLength = sqrt( normX * normX + normY * normY);
      
      normX = normX / normLength;
      normY = normY / normLength;

      // Get projection of movement vectors onto normal
      // (Dot prod each with norm)

      double myProj    = (myXvel * normX) + 
	                 (myYvel * normY);

      double otherProj = (other.myXvel * normX) +
                         (other.myYvel * normY);

      // Now, factor in impulse, derived from
      // Conservation of Energy / Conservation of Momentum

      double P = ( 2 * (myProj - otherProj) );

      P = P / (myMass + other.myMass);

      
      double v1f_X = myXvel - (P * other.myMass * normX);
      double v1f_Y = myYvel - (P * other.myMass * normY);

      double v2f_X = other.myXvel + (P * myMass * normX);
      double v2f_Y = other.myYvel + (P * myMass * normY);
      


      // reset velues in balls
      adjust(myXaccel, myYaccel, v1f_X, v1f_Y, 
	     myXpos, myYpos, myXpos, myYpos);

      other.adjust(other.myXaccel, other.myYaccel,
		   v2f_X, v2f_Y,
		   other.myXpos, other.myYpos,
		   other.myXpos, other.myYpos);

      

      //justCollided = true;
      //other.justCollided = true;
    
    } 


}
      
      
      
