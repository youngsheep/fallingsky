#ifndef __CONNECTION_OBJECT_H__
#define __CONNECTION_OBJECT_H__

#include "jansson.hpp"

class ConnectObject
{
public:
	virtual void RequestCallback(json::Value& data) = 0;
	virtual json_t * GetJson() = 0;
	virtual void PushCallback(json::Value& data) = 0;
};
#endif