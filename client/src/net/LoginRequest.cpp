#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::DoLogin(const char* uid,const char* access_token)
{
    std::string route("connector.entryHandler.entry");
    json::Value req(json::object());
    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("pid",json::Value(0));
	head.set_key("uid",json::Value(uid));

    req.set_key("head",head);
	req.set_key("token",json::Value(access_token));

    DoRequest(req,route,&GameProtoHandler::OnLogin);

    FLPlayer::GetInstance().SetUid(uid);
}

void GameProtoHandler::OnLogin(json::Value data,const char* route)
{
    printf("recv login response!\n");
    int result = data["result"].as_integer();
    int playerid = data["pid"].as_integer();
    if (result == 0)
    {
        FLPlayer::GetInstance().SetPlayerID(playerid);
    }
    else
    {
        if (result == 100)
        {
            const char* nickname = data["nickname"].as_cstring();
            FLPlayer::GetInstance().SetPlayerID(playerid);
            FLPlayer::GetInstance().SetNickName(nickname);
        }
        else
        {
            FLPlayer::GetInstance().SetUid("");
        }
    }
    RemoveRequest(std::string(route));
}