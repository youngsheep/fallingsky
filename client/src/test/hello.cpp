#include "common/PomeloConnection.h"
#include "net/LoginRequest.h"
#include "net/BattleRequest.h"
#include "entity/FLBattle.h"
#include "config/srcgen/testConfigHolder.h"

const char *ip = "127.0.0.1";
int port = 3010;

int main() {

    testConfigHolder testHolder;
    testHolder.LoadConfig();

	PomeloConnection::getInstance().Connect(ip,port);

    FLBattle battle;
	LoginRequest login;
    BattleRequest battlereq(battle);

    char input[6];

    printf("Input a line to send message to server and input `end` to exit.\n");
    while(1) {
        scanf("%s", input);
        if(!strcmp(input, "end")) {
            break;
        }
        else if (!strcmp(input, "login"))
        {
            login.DoLogin();
        }
        else if (!strcmp(input, "start"))
        {
            battlereq.StartBattleReq();
        }
        else if (!strcmp(input, "cmd"))
        {
            if (battle.GetState() == FL_BATTLE_STATE_START)
            {
                battlereq.BattleCmdReq(battle.GetID(),2,2,0);
            }
        }
    }

	return 0;
}
