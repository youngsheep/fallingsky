#ifndef __ENTITY_FLBATTLE_H__
#define __ENTITY_FLBATTLE_H__

#include "common/jansson.hpp"

#define MAX_USERNAME_LEN 64

enum 
{
    FL_BATTLE_STATE_NOT_INIT = 0,
    FL_BATTLE_STATE_START,
    FL_BATTLE_STATE_END
};

enum 
{
    FL_BATTLE_TYPE_PVE = 1,
    FL_BATTLE_TYPE_PVP
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
    int GetType(){return m_battleType;}
    const char* GetOppName(){return m_oppname;}
    int PickNextBlock()
    {
        int next = m_nextBlock;
        m_nextBlock = -1;
        return next;
    }

protected:
    int m_BattleState;

    int m_battleid;
    int m_battleType;

    int m_nextBlock;
    int m_clearLines[4];

    int m_oppid;
    char m_oppname[MAX_USERNAME_LEN];
    int m_oppBlock;


};
#endif