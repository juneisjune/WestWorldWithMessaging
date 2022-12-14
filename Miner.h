#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "MinerOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of gold a miner must have before he feels he can go home
const int HeadacheLevel       = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets         = 3;
//above this value a miner is thirsty
const int KnowLevel        = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;



class Miner : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Miner>*  m_pStateMachine;
  
  location_type         m_Location;

  //how many nuggets the miner has in his pockets
  int                   m_iGoldCarried;

  int                   m_iHeadaheLevel;

  //the higher the value, the thirstier the miner
  int                   m_iKnow;

  //the higher the value, the more tired the miner
  int                   m_iFatigue;
  int valueOfDoSideProject;
  int valueWhenFinishingSiedProject;

public:

  Miner(int id):m_Location(sideproject),
                          m_iGoldCarried(0),
                         m_iHeadaheLevel(0),
                             m_iKnow(0),
                          m_iFatigue(0),
                          valueOfDoSideProject(0),
                          valueWhenFinishingSiedProject(0),
                          BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<Miner>(this);
    
    m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
  }

  ~Miner(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  
  StateMachine<Miner>* GetFSM()const{return m_pStateMachine;}


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    
  int           GoldCarried()const{return m_iGoldCarried;}
  void          SetGoldCarried(int val){m_iGoldCarried = val;}
  void          AddToGoldCarried(int val);
  bool          PocketsFull()const{return m_iGoldCarried >= MaxNuggets;}

  int           Fatigued();
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  int           GetDoSideProject(){ return valueOfDoSideProject; }
  void          IncreasSideProject(){ valueOfDoSideProject += 1; }

  int           WhenFinishingProject() { return valueWhenFinishingSiedProject; }
  void          IncreaseWhenFinishingProject() { valueWhenFinishingSiedProject += 1; }

  int           Wealth(){return m_iHeadaheLevel;}
  void          SetWealth(int val){ m_iHeadaheLevel = val;}
  void          AddToWealth(int val);

  bool          Thirsty()const; 
  void          BuyAndDrinkAWhiskey(){ m_iKnow = 0; m_iHeadaheLevel -=2;}

};



#endif
