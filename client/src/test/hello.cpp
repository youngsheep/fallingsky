#include "common/PomeloConnection.h"
#include "net/LoginRequest.h"

const char *ip = "127.0.0.1";
int port = 3010;

int main() {

	PomeloConnection::getInstance().Connect(ip,port);

	static LoginRequest login;
	login.DoLogin();

	return 0;
}
