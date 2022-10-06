#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Senior programmer";

  case ent_Elsa:
    
    return "Junior programmer"; 

  default:

    return "UNKNOWN!";
  }
}

#endif