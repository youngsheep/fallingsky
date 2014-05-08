#include "LoginRequest.h"
#include "common/PomeloConnection.h"

void LoginRequest::RequestCallback(json::Value& data,const char* route)
{

}

void LoginRequest::DoLogin()
{
	m_req.clear();
    
    json::Value head(json::object());

    head.set_key("magic",json::Value(PROTO_MAGIC));
    head.set_key("playerid",json::Value(0));

    m_req.set_key("head",head);
	m_req.set_key("username",json::Value("aaa"));
	m_req.set_key("token",json::Value("bbb"));

	PomeloConnection::getInstance().DoRequest(this,m_req,"connector.entryHandler.entry");
}