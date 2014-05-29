#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::StartBattleReq(int type)
{
    FLPlayer& player = FLPlayer::GetInstance();

    std::string route("game.battleHandler.start");
    json::Value req(json::object());
    req.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("pid",json::Value(player.GetPlayerID()));
    head.set_key("uid",json::Value(player.GetUid()));

    req.set_key("head",head);
    req.set_key("type",json::Value(type));

    DoRequest(req,route,pomelo_selector(GameProtoHandler::OnStartBattle));
}

int GameProtoHandler::OnStartBattle(json::Value data,const char* route)
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
    return result;
}

void GameProtoHandler::BattleCmdReq(int xpos,int ypos,int flag)
{
    FLPlayer& player = FLPlayer::GetInstance();

    std::string route("game.battleHandler.cmd");
    json::Value req(json::object());
    req.clear();

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("pid",json::Value(player.GetPlayerID()));
    head.set_key("uid",json::Value(player.GetUid()));

    req.set_key("head",head);
    req.set_key("battleid",json::Value(player.GetBattle().GetID()));
    req.set_key("xPos",json::Value(xpos));
    req.set_key("yPos",json::Value(ypos));
    req.set_key("rotateFlag",json::Value(flag));
     
    DoRequest(req,route,pomelo_selector(GameProtoHandler::OnBattleCmd));
}

int GameProtoHandler::OnBattleCmd(json::Value data,const char* route)
{
    printf("recv battle cmd resp!\n");
    int result = data["result"].as_integer();
    if (result == 0)
    {
        printf("battle cmd success !\n");
        FLPlayer::GetInstance().GetBattle().Update(data);
    }
    else
    {
        printf("fail battle cmd!\n");
    }
    RemoveCallBack(route);
    return 0;
}