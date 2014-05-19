#include "FLBattle.h"

FLBattle::FLBattle()
    : m_BattleState(FL_BATTLE_STATE_NOT_INIT)
    , m_battleid(-1)
    , m_oppid(-1)
    , m_nextBlock(-1)
{
    memset(m_oppname,0x0,MAX_USERNAME_LEN);
    memset(m_clearLines,0x0,sizeof(int)*4);
}

void FLBattle::Init(json::Value& data)
{
    m_battleid = data["battleid"].as_integer();
    m_oppid = data["oppId"].as_integer();
    std::string name = data["oppName"].as_string();
    strncpy(m_oppname,name.c_str(),name.size());
    m_nextBlock = data["firstBlock"].as_integer();

    SetState(FL_BATTLE_STATE_START);
    printf("battle start! battle id: %d  , oppid:%d ,oppName:%s  \n",m_battleid,m_oppid,m_oppname);
}

void FLBattle::Update(json::Value& data)
{
    json::Value lines(data["clearLines"].as_json());
    if (lines.is_array())
    {
        for (unsigned int i = 0 ; i < lines.size() && i < 4; i++)
        {
            m_clearLines[i] = lines.at(i).as_integer();
        }
    }
    m_nextBlock = data["nextType"].as_integer();

    printf("battle update :%s  \n",data.save_string());
}

