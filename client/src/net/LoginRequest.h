#ifndef __LOGIN_REQUEST_H__
#define __LOGIN_REQUEST_H__

#include "common/ConnectionObject.h"

class LoginRequest: public RequestDeletegate
{
public:
	LoginRequest():
	  m_req(json::object())
	{}
	virtual ~LoginRequest()
	{}

	virtual void RequestCallback(json::Value& data,const char* route);

	void DoLogin();
protected:
	json::Value m_req;
};
#endif
