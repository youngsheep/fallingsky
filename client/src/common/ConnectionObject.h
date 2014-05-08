#ifndef __CONNECTION_OBJECT_H__
#define __CONNECTION_OBJECT_H__

#include "jansson.hpp"

class RequestDeletegate
{
public:
	virtual void RequestCallback(json::Value& data,const char* route) = 0;
};

class PushEventListener
{
public:
    virtual void PushCallback(json::Value& data) = 0;
};
#endif