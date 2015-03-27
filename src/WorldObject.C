#include "WorldObject.H"


/* elapsedTime is num of nanoseconds since the last time
   the system loop updated. This method allows this object to 
   update itself accordingly
   
   By default

*/
void WorldObject::update(long elapsedTime)
{
  //x(t) = x(0) + v(0)T + 1/2aT^2

  long int T_squared = elapsedTime * elapsedTime;

  newXpos = 
    myXpos 
    + (myXvel * elapsedTime) 
    + ((0.5) * (myXaccel)) * (T_squared);

  newYpos = 
    myYpos
    + (myYvel * elapsedTime)
    + ((0.5) * (myYaccel)) * (T_squared);
  
  //myXpos = newXpos;
  //myYpos = newYpos;

  //adjust new velocity

  double newXvel = 
    myXvel + (myXaccel * elapsedTime);

  double newYvel = 
    myYvel + (myYaccel * elapsedTime);

  
  myXvel = newXvel;
  myYvel = newYvel;

  //primitive error checking
  if(newXpos < 0) {
    newXpos = 0;
    myXvel = -(myXvel * VELOC_LOSS);
    myXaccel = 0;

    if(crash != NULL)
      crash->playNow();
  }

  if(newYpos < 0) {
    newYpos = 0;
    myYvel = -(myYvel * VELOC_LOSS);
    myYaccel = 0;

    if(crash != NULL)
      crash->play();
  }

  if(newXpos > myXmax) {
    newXpos = myXmax;
    myXvel = -(myXvel * VELOC_LOSS);
    myXaccel = 0;

    if(crash != NULL)
      crash->play();
  }

  if(newYpos > myYmax) {
    newYpos = myYmax;
    myYvel = -(myYvel * VELOC_LOSS);
    myYaccel = 0;

    if(crash != NULL)
      crash->play();
  }

  /*
  if(elapsedTime % 1 == 0)
    {
      cerr << "myXaccel: " << myXaccel << ";  "
	   << "myXvel: " << myXvel << ";  "
	   << "myXpos: " << myXpos << ";  "
	   << "elapsedTime: " << elapsedTime << endl;
    }
  */



}


void WorldObject::ok()
{
  myXpos = newXpos;
  myYpos = newYpos;
}






void WorldObject::adjust(double Xaccel, double Yaccel,
			 double Xvel, double Yvel,
			 double Xpos, double Ypos,
			 double newX, double newY)
{
  myXaccel = Xaccel;
  myYaccel = Yaccel;

  myXvel = Xvel;
  myYvel = Yvel;
  
  myXpos = Xpos;
  myYpos = Ypos;

  newXpos = newX;
  newYpos = newY;

}









Sprite* WorldObject::getCurrentSprite()
{
  return states[currentSprite];
}






void WorldObject::setState(states_generic newState)
{ 
  currentSprite = newState; 

  switch(newState) {
  case FLOAT:
  case DEAD:
    myXaccel = 0;
    myYaccel = 0;
    break;
  case UP_LEFT:
    myXaccel = -ACCEL_RATE;
    myYaccel = -ACCEL_RATE;
    break;
  case UP:
    myXaccel = 0;
    myYaccel = -ACCEL_RATE;
    break;
  case UP_RIGHT:
    myXaccel = ACCEL_RATE;
    myYaccel = -ACCEL_RATE;
    break;
  case RIGHT:
    myXaccel = ACCEL_RATE;
    myYaccel = 0;
    break;
  case DOWN_RIGHT:
    myXaccel = ACCEL_RATE;
    myYaccel = ACCEL_RATE;
    break;
  case DOWN:
    myXaccel = 0;
    myYaccel = ACCEL_RATE;
    break;
  case DOWN_LEFT:
    myXaccel = -ACCEL_RATE;
    myYaccel = ACCEL_RATE;
    break;
  case LEFT:
    myXaccel = -ACCEL_RATE;
    myYaccel = 0;
    break;
      
  }


}


unsigned int WorldObject::getState()
{
  return currentSprite;
}




void WorldObject::draw(SDL_Surface* dest)
{
  /*
  cerr << "Calling draw on states[" << currentSprite
       << "] or " << states[currentSprite] << endl;
  */
  getCurrentSprite()->draw(dest, (int)myXpos, (int)myYpos);
}
  

void WorldObject::erase()
{
  getCurrentSprite()->erase();
}
