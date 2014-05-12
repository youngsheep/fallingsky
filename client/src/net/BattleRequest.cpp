#include "BattleRequest.h"
#include "common/PomeloConnection.h"
#include "entity/FLBattle.h"

void BattleRequest::RequestCallback(json::Value& data,const char* route)
{
    if (strncmp(route,"game.battleHandler.start",MAX_ROUTE_LEN) == 0)
    {
        m_Battle.Init(data);
        m_startReq.clear();
    }
    else if (strncmp(route,"game.battleHandler.cmd",MAX_ROUTE_LEN) == 0)
    {
        m_Battle.Update(data);
        m_cmdReq.clear();
    }
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

    PomeloConnection::getInstance().DoRequest(this,m_startReq,"game.battleHandler.start");
}

void BattleRequest::BattleCmdReq(int battleid,int xpos,int ypos,int flag)
{
    m_cmdReq.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));

    m_cmdReq.set_key("head",head);
    m_cmdReq.set_key("battleid",json::Value(battleid));
    m_cmdReq.set_key("xPos",json::Value(xpos));
    m_cmdReq.set_key("yPos",json::Value(ypos));
    m_cmdReq.set_key("rotateFlag",json::Value(flag));

    PomeloConnection::getInstance().DoRequest(this,m_cmdReq,"game.battleHandler.cmd");
}