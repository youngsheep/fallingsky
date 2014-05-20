#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::RoleCreateReq(const char* name)
{
    FLPlayer& player = FLPlayer::GetInstance();

    std::string route = "game.roleHandler.register";
    json::Value req(json::object());

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(player.GetPlayerID()));
    head.set_key("username",json::Value(player.GetUserName()));

    req.set_key("head",head);
    req.set_key("nickname",json::Value(name));

    DoRequest(req,route,&GameProtoHandler::OnRoleCreate);
}

void GameProtoHandler::OnRoleCreate(json::Value data,const char* route)
{
    printf("recv role create response!\n");
    int result = data["result"].as_integer();

    if (result == 0)
    {
    }
    else
    {
    }

    RemoveRequest(route);
}

void GameProtoHandler::RoleInfoReq()
{
    FLPlayer& player = FLPlayer::GetInstance();

    std::string route = "game.roleHandler.info";
    json::Value req(json::object());

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(player.GetPlayerID()));
    head.set_key("username",json::Value(player.GetUserName()));

    req.set_key("head",head);

    DoRequest(req,route,&GameProtoHandler::OnRoleCreate);
}

void GameProtoHandler::OnRoleInfo(json::Value data,const char* route)
{
    printf("recv role info response!\n");
    int result = data["result"].as_integer();

    if (result == 0)
    {
    }
    else
    {
    }

    RemoveRequest(route);
}