#include "common/PomeloConnection.h"
#include "net/GameProtoHandler.h"
#include "entity/FLPlayer.h"
#include "config/srcgen/testConfigHolder.h"

const char *ip = "198.199.100.95";
int port = 3010;

int main() {
    char input[64];

    //testConfigHolder testHolder;
    //testHolder.LoadConfig();

    FLPlayer& player = FLPlayer::GetInstance();
	GameProtoHandler& handler = GameProtoHandler::GetInstance();
    handler.ConnectGameSvr(ip,port);
    handler.AddAllPushEvent();
    handler.DoLogin("1449516883","2.00ZYBGaBrInXhC5fd379312ddlQZkB");

    while(1) {
        if ( !handler.IsWait())
        {
            printf("\n\nInput cmd:");
            scanf("%s", input);
            if(!strcmp(input, "end")) {
                break;
            }
            else if (!strcmp(input, "create"))
            {
                printf("Input nickname to register : ");
                scanf("%s", input);
                handler.RoleCreateReq(input);
            }
            else if (!strcmp(input, "info"))
            {
                handler.RoleInfoReq();
            }
            else if (!strcmp(input, "start"))
            {
                handler.StartBattleReq(1);
            }
            else if (!strcmp(input, "cmd"))
            {
                if (player.GetBattle().GetState() == FL_BATTLE_STATE_START)
                {
                    handler.BattleCmdReq(player.GetBattle().GetID(),1,1,0);
                    handler.BattleCmdReq(player.GetBattle().GetID(),1,3,0);
                    handler.BattleCmdReq(player.GetBattle().GetID(),1,5,0);
                    handler.BattleCmdReq(player.GetBattle().GetID(),1,7,0);
                }
            }
        }
        handler.GetConn().update(0);
    }

	return 0;
}
