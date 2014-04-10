#ifndef __LOGIN_REQUEST_H__
#define __LOGIN_REQUEST_H__

#include "common/ConnectionObject.h"

class LoginRequest: public ConnectObject
{
public:
	LoginRequest();
	virtual ~LoginRequest();

	virtual void RequestCallback(json::Value& data);
	virtual json_t* GetJson();
	virtual void PushCallback(json::Value& data);

protected:
	json::Value m_req;
};
#endif
