#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_StartSideProject,
  Msg_FinishSideProject,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case   Msg_StartSideProject:
    
    return "StartSideProject"; 

  case Msg_FinishSideProject:
    
    return "FinishSideProject";

  default:

    return "Not recognized!";
  }
}

#endif