#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

int GameProtoHandler::OnRoleBaseInfo(json::Value data,const char* route)
{
    printf("recv role base info push ! \n");
    return 0;
}

int GameProtoHandler::OnOppState(json::Value data,const char* route)
{
    printf("recv opp state push ! \n");
    return 0;
}