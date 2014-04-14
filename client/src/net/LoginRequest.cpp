#include "LoginRequest.h"
#include "common/PomeloConnection.h"

void LoginRequest::RequestCallback(json::Value& data)
{

}

void LoginRequest::PushCallback(json::Value& data)
{

}

void LoginRequest::DoLogin()
{
	m_req.clear();

	json::Value name("aaa");
	json::Value passwd("bbb");

	m_req.set_key("username",name);
	m_req.set_key("passwd",passwd);

	PomeloConnection::getInstance().DoRequest(this,"connector.entryHandler.entry");
}