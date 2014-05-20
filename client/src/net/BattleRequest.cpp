#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::StartBattleReq()
{
    std::string route("game.battleHandler.start");
    json::Value req(json::object());
    req.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));

    req.set_key("head",head);
    req.set_key("type",json::Value(0));

    DoRequest(req,route,&GameProtoHandler::OnStartBattle);
}

void GameProtoHandler::OnStartBattle(json::Value data,const char* route)
{
    int result = data["result"].as_integer();
    if (result == 0)
    {
        printf("success start battle !\n");
        FLPlayer::GetInstance().GetBattle().Init(data);
    }
    else
    {
        printf("fail to start battle!\n");
    }
    RemoveRequest(route);
}

void GameProtoHandler::BattleCmdReq(int battleid,int xpos,int ypos,int flag)
{
    std::string route("game.battleHandler.cmd");
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

    DoRequest(req,route,&GameProtoHandler::OnBattleCmd);
}

void GameProtoHandler::OnBattleCmd(json::Value data,const char* route)
{
    printf("recv battle cmd resp!\n");
    RemoveRequest(route);
}