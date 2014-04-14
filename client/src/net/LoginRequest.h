#ifndef __LOGIN_REQUEST_H__
#define __LOGIN_REQUEST_H__

#include "common/ConnectionObject.h"

class LoginRequest: public ConnectObject
{
public:
	LoginRequest():
	  m_req(json::object())
	{}
	virtual ~LoginRequest()
	{}

	virtual void RequestCallback(json::Value& data);
	virtual json_t* GetJson(){return m_req.as_json();}
	virtual void PushCallback(json::Value& data);

	void DoLogin();
protected:
	json::Value m_req;
};
#endif
