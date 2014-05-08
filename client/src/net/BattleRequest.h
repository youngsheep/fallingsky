#ifndef __NET_BATTLE_REQUEST_H__
#define __NET_BATTLE_REQUEST_H__

#include "common/ConnectionObject.h"

class BattleRequest: public ConnectObject
{
public:
    BattleRequest()
        : m_startReq(json::object())
        , m_cmdReq(json::object())
    {}
    virtual ~BattleRequest()
    {}

    virtual void RequestCallback(json::Value& data);
    virtual json_t* GetJson(){return m_req.as_json();}
    virtual void PushCallback(json::Value& data);

    void StartBattleReq();
    void BattleCmdReq();

protected:
    json::Value m_startReq;
    json::Value m_cmdReq;
};
#endif