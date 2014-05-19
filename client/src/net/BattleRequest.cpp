#include "GameProtoHandler.h"

void GameProtoHandler::StartBattleReq()
{
    json::Value req(json::object());
    req.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));

    req.set_key("head",head);
    req.set_key("type",json::Value(0));

    m_pomeloConn.DoRequest(this,req,"game.battleHandler.start");
}

void GameProtoHandler::BattleCmdReq(int battleid,int xpos,int ypos,int flag)
{
    json::Value req(json::object());
    req.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));

    req.set_key("head",head);
    req.set_key("battleid",json::Value(battleid));
    req.set_key("xPos",json::Value(xpos));
    req.set_key("yPos",json::Value(ypos));
    req.set_key("rotateFlag",json::Value(flag));

    m_pomeloConn.DoRequest(this,req,"game.battleHandler.cmd");
}