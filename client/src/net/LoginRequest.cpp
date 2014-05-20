#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::DoLogin(const char* name)
{
    std::string route("connector.entryHandler.entry");
    json::Value req(json::object());
    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));
	head.set_key("username",json::Value(name));

    req.set_key("head",head);
	req.set_key("token",json::Value("bbb"));

    DoRequest(req,route,&GameProtoHandler::OnLogin);

    FLPlayer::GetInstance().SetUserName(name);
}

void GameProtoHandler::OnLogin(json::Value data,const char* route)
{
    printf("recv login response!\n");
    int result = data["result"].as_integer();

    if (result == 0)
    {
        int playerid = data["playerid"].as_integer();
        FLPlayer::GetInstance().SetPlayerID(playerid);
    }
    else
    {
        if (result == 100)
        {
            int playerid = data["playerid"].as_integer();
            FLPlayer::GetInstance().SetPlayerID(playerid);
        }
        else
        {
            FLPlayer::GetInstance().SetUserName("");
        }
    }
    RemoveRequest(std::string(route));
}