#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Junior = new Miner(ent_Junior_Programmer);

  //create his wife
  MinersWife* Senior = new MinersWife(ent_Senior_Programmer);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Junior);
  EntityMgr->RegisterEntity(Senior);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Junior->Update();
    Senior->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Junior;
  delete Senior;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






