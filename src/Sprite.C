#include "Sprite.H"



Sprite::Sprite(char* PNG_filename)
{
  anim = false;
  myAnim = 0;

  myImg = IMG_Load(PNG_filename);
  
  if (myImg == NULL) {
    throw PlatformerException("Error loading file.");
  }

  myHeight = myImg->h;
  myWidth = myImg->w;

  name = PNG_filename;

  myLastX = 0;
  myLastY = 0;
  myLast = NULL;
}




Sprite::Sprite(SDL_Surface* image)
{
  anim = false;

  myImg = image;

  myHeight = myImg->h;
  myWidth = myImg->w;

  name = "null";
}




Sprite::Sprite(Animation* animation)
{
  anim = true;

  // TODO: implement this method

}




void Sprite::draw(SDL_Surface* dest, 
		  int x, int y)
{
  /*
  if(!anim)
    cerr << "Now drawing: " << name << endl;
  
  */

  SDL_Rect rct;
  rct.x = x;
  rct.y = y;
  rct.w = myWidth;
  rct.h = myHeight;
 
  if(!anim)
    {
      SDL_SetColorKey(myImg, SDL_SRCCOLORKEY, 0xffffff);
      
      if(SDL_BlitSurface(myImg, NULL, dest, &rct) < 0)
	throw PlatformerException("Error drawing sprite!");
      
      
      // keep this?
      // SDL_UpdateRect(dest, x, y, myWidth, myHeight);
    }

  myLastX = x;
  myLastY = y;
  myLast = dest;


}


/* This method should really only be used if you want to use
   the 'UpdateRect' method of screen refreshing.

   It prevents 'trails'
*/
void Sprite::erase()
{
  /*
  SDL_Rect rct;
  rct.x = myLastX;
  rct.y = myLastY;
  rct.w = myWidth;
  rct.h = myHeight;
  */

  //  SDL_FillRect(myLast, &rct, BLACK);

  //SDL_UpdateRect(myLast, myLastX, myLastY, myWidth, myHeight);

}






void Sprite::update(long elapsedTime)
{
  if(anim)
    myAnim->update(elapsedTime);
}
