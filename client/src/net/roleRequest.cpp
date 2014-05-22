#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::RoleCreateReq(const char* name)
{
    FLPlayer& player = FLPlayer::GetInstance();

    std::string route = "game.roleHandler.register";
    json::Value req(json::object());

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("pid",json::Value(player.GetPlayerID()));
    head.set_key("uid",json::Value(player.GetUid()));

    req.set_key("head",head);
    if (name == NULL || strlen(name) == 0)
    {
        req.set_key("nickname",json::Value(player.GetNickName()));
    }
    else
    {
        req.set_key("nickname",json::Value(name));
    }

    DoRequest(req,route,pomelo_selector(GameProtoHandler::OnRoleCreate));
}

int GameProtoHandler::OnRoleCreate(json::Value data,const char* route)
{
    printf("recv role create response!\n");
    int result = data["result"].as_integer();

    if (result == 0)
    {
    }
    else
    {
    }

    RemoveCallBack(route);
    return  result;
}

void GameProtoHandler::RoleInfoReq()
{
    FLPlayer& player = FLPlayer::GetInstance();

    std::string route = "game.roleHandler.info";
    json::Value req(json::object());

    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("pid",json::Value(player.GetPlayerID()));
    head.set_key("uid",json::Value(player.GetUid()));

    req.set_key("head",head);

    DoRequest(req,route,pomelo_selector(GameProtoHandler::OnRoleCreate));
}

int GameProtoHandler::OnRoleInfo(json::Value data,const char* route)
{
    printf("recv role info response!\n");
    int result = data["result"].as_integer();

    if (result == 0)
    {
    }
    else
    {
    }

    RemoveCallBack(route);
    return result;
}