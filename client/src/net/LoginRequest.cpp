#include "GameProtoHandler.h"

void GameProtoHandler::DoLogin()
{
    json::Value req(json::object());

	req.clear();
    
    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));
	head.set_key("username",json::Value("aaa"));

    req.set_key("head",head);
	req.set_key("token",json::Value("bbb"));

	m_pomeloConn.DoRequest(this,req,"connector.entryHandler.entry");
}