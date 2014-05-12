#ifndef __ENTITY_FLBATTLE_H__
#define __ENTITY_FLBATTLE_H__

#include "common/jansson.hpp"
#include "net/BattleRequest.h"

#define MAX_USERNAME_LEN 64

enum 
{
    FL_BATTLE_STATE_NOT_INIT = 0,
    FL_BATTLE_STATE_START,
    FL_BATTLE_STATE_END
};
class FLBattle
{
public:
    FLBattle();
    ~FLBattle(){}

    void Init(json::Value& data);
    void Update(json::Value& data);

    int GetState(){return m_BattleState;}
    void SetState(int state){m_BattleState = state;}

    int GetID(){return m_battleid;}
    int GetOppID(){return m_oppid;}
    const char* GetOppName(){return m_oppname;}
    int PickNextBlock()
    {
        int next = m_nextBlock;
        m_nextBlock = -1;
        return next;
    }
    
    BattleRequest& GetRequest(){return m_battleReq;}
    
protected:
    int m_BattleState;

    int m_battleid;
    int m_oppid;
    char m_oppname[MAX_USERNAME_LEN];

    int m_nextBlock;
    int m_clearLines[4];
    
    BattleRequest m_battleReq;
};
#endif