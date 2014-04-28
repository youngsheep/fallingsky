#include "common/PomeloConnection.h"
#include "net/LoginRequest.h"
#include "config/srcgen/testConfigHolder.h"

const char *ip = "127.0.0.1";
int port = 3010;

int main() {

    testConfigHolder testHolder;
    testHolder.LoadConfig();

	PomeloConnection::getInstance().Connect(ip,port);

	static LoginRequest login;

    char input[6];

    printf("Input a line to send message to server and input `bye` to exit.\n");
    while(1) {
        scanf("%s", input);
        if(!strcmp(input, "end")) {
            break;
        }
        else if (!strcmp(input, "login"))
        {
            login.DoLogin();
        }
    }

	return 0;
}
