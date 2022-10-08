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

    return "Junior programmer";

  case ent_Elsa:
    
    return "Senior programmer"; 

  default:

    return "UNKNOWN!";
  }
}

#endif