#include "GameProtoHandler.h"
#include "entity/FLPlayer.h"

void GameProtoHandler::OnRoleBaseInfo(json::Value data,const char* route)
{
    printf("recv role base info push ! \n");
}

void GameProtoHandler::OnOppState(json::Value data,const char* route)
{
    printf("recv opp state push ! \n");
}