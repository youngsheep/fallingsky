#include "common/PomeloConnection.h"
#include "net/GameProtoHandler.h"
#include "entity/FLPlayer.h"
#include "config/srcgen/testConfigHolder.h"

const char *ip = "127.0.0.1";
int port = 3010;

int main() {

    testConfigHolder testHolder;
    testHolder.LoadConfig();

    FLPlayer& player = FLPlayer::GetInstance();
	GameProtoHandler& handler = GameProtoHandler::GetInstance();
    handler.ConnectGameSvr(ip,port);

    char input[6];

    printf("Input a line to send message to server and input `end` to exit.\n");
    while(1) {
        scanf("%s", input);
        if(!strcmp(input, "end")) {
            break;
        }
        else if (!strcmp(input, "login"))
        {
            handler.DoLogin();
        }
        else if (!strcmp(input, "start"))
        {
            handler.StartBattleReq();
        }
        else if (!strcmp(input, "cmd"))
        {
            if (player.GetBattle().GetState() == FL_BATTLE_STATE_START)
            {
                handler.BattleCmdReq(player.GetBattle().GetID(),2,2,0);
            }
        }
    }

	return 0;
}
