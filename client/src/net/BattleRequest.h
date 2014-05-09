#ifndef __NET_BATTLE_REQUEST_H__
#define __NET_BATTLE_REQUEST_H__

#include "common/ConnectionObject.h"

class FLBattle;
class BattleRequest: public RequestDeletegate
{
public:
    BattleRequest(FLBattle& battle)
        : m_startReq(json::object())
        , m_cmdReq(json::object())
        , m_Battle(battle)
    {}
    virtual ~BattleRequest()
    {}

    virtual void RequestCallback(json::Value& data,const char* route);
    virtual void PushCallback(json::Value& data);

    void StartBattleReq();
    void BattleCmdReq(int battleid,int xpos,int ypos,int flag);

protected:
    json::Value m_startReq;
    json::Value m_cmdReq;
    FLBattle& m_Battle;
};
#endif