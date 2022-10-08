#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Junior_Programmer,

  ent_Senior_Programmer

};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Junior_Programmer:

    return "Junior programmer";

  case ent_Senior_Programmer:
    
    return "Senior programmer"; 

  default:

    return "UNKNOWN!";
  }
}

#endif