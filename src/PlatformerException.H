#ifndef PLATEXCEPT
#define PLATEXCEPT

#include <iostream>

using namespace std;

class PlatformerException : std::exception
{

public:

  PlatformerException(char* mess) {
    message = mess;
  }

  char* what()
  {
    return message;
  }


private:
  char* message;

};
 


#endif
