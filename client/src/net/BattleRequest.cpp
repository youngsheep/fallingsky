#include "BattleRequest.h"

void BattleRequest::RequestCallback(json::Value& data)
{

}

void BattleRequest::PushCallback(json::Value& data)
{

}

void BattleRequest::StartBattleReq()
{
    m_startReq.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));

    m_startReq.set_key("head",head);
    m_startReq.set_key("type",json::Value(0));

    PomeloConnection::getInstance().DoRequest(this,"battle.battleHandler.start");
}

void BattleRequest::BattleCmdReq()
{

}