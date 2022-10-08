#include "MinerOwnedStates.h"
#include "fsm/State.h"
#include "Miner.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
  //if the miner is not already located at the goldmine, he must
  //change location to the gold mine
  if (pMiner->Location() != office)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walking to office for programming ";//Walkin' to the goldmine

    pMiner->ChangeLocation(office);
  }
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{  
  //Now the miner is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Respond an issue "; //Pickin' up a nugget

  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull())
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pMiner->Thirsty())
  {
    pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "I have headache i can't do anymore ";//Ah'm leavin' the goldmine with mah pockets full o' sweet gold
}
//I can't solve this error. I'm going to ask my senior

bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != restRoom)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Way to rest room is too far";//Goin' to the bank. Yes siree

    pMiner->ChangeLocation(restRoom);
  }
}
//Way to senior programmer office

void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
      << "I going to sleep few minutes"/* << pMiner->Wealth()*/;//Depositing gold. Total savings now: 

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
         << "WooHoo! Headache is gone. Go back to office for work";//WooHoo! Rich enough for now. Back home to mah li'lle lady
      
    pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      
  }

  //otherwise get more gold
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the rest room";//Leavin' the bank
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
  if (pMiner->Location() != sideproject)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
        << "I have to go home because my working hours are over, \n                   but I have to go for side projects with a senior programmer";
    //Walkin' home
    pMiner->ChangeLocation(sideproject);

    //let the wife know I'm home
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Senior_Programmer,            //ID of recipient
                                Msg_StartSideProject,   //the message
                              NO_ADDITIONAL_INFO);    
  }
}
//int i = 0;
//int z = 0;
void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
    
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued())
  {
     cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
          << "OMG :( It's already morning. Time to work for payback an apartment loan";//All mah fatigue has drained away. Time to find more gold!

     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
  else if (pMiner->GetDoSideProject() < 2)
  {
      pMiner->IncreaseFatigue();
      cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Doing side project ";
      pMiner->IncreasSideProject();
      //i++;
      goto out;
      
  }
  
  else 
  {
    //sleep
    pMiner->DecreaseFatigue();
    if (pMiner->WhenFinishingProject() == 0)
    {
        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
            << "I arrived home and took a shower. Now I'm going to sleep";
        pMiner->IncreaseWhenFinishingProject();
    }
            cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ...";
  } 
out:
  {}
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{ 
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_FinishSideProject:

     cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) 
     << " at time: " << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pMiner->ID()) 
          << ": Oh yes, I did everything. ";
     //Okay Hun, ahm a comin'!
     pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
  if (pMiner->Location() != meatingRoom)
  {    
    pMiner->ChangeLocation(meatingRoom);

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "The meeting is start soon, i need to hurry up";
  }//Boy, ah sure is thusty! Walking to the saloon
}

void QuenchThirst::Execute(Miner* pMiner)
{
  pMiner->BuyAndDrinkAWhiskey();

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "It was nice meeting ";
  //That's mighty fine sippin' liquer
  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void QuenchThirst::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the meeting room";
}// Leaving the saloon, feelin' good


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
   // Smells Reaaal goood Elsa!
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Can i go home?";
}

void EatStew::Execute(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Tastes real good too!";

  pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


