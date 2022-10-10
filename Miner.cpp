#include "Miner.h"

bool Miner::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Miner::Update()
{
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

  m_iKnow += 1;
  
  m_pStateMachine->Update();
}



void Miner::AddToGoldCarried(const int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Miner::AddToWealth(const int val)
{
    m_iHeadaheLevel += val;

  if (m_iHeadaheLevel < 0)
  {
      m_iHeadaheLevel = 0;
  }
}

bool Miner::Thirsty()const
{
  if (m_iKnow >= KnowLevel){return true;}

  return false;
}

int Miner::Fatigued()
{
  if (m_iFatigue > TirednessThreshold) //현재 피로가 기준점보다 크다면
  {
    return true;
  }

  return false;
}
