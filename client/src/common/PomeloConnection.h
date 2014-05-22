#ifndef __FS_CONNECTION_H__
#define __FS_CONNECTION_H__

#include <map>
#include <string>
#include <list>
#include "jansson.hpp"
#include "cocoa/CCObject.h"

#define PROTO_MAGIC 1101
#define MAX_ROUTE_LEN 128

struct pc_client_s;

class IPomeloConnection
{
public:
    virtual void ProtoHandlerCallback(json::Value& data,const char* route,bool isPush) = 0;
};

typedef int (IPomeloConnection::*ProtoCallBack)(json::Value data,const char* route);
#define pomelo_selector(_SELECTOR) (ProtoCallBack)(&_SELECTOR)

struct PomeloMsg
{
    char _route[MAX_ROUTE_LEN];
    json::Value _data;
    bool _isPush;

    PomeloMsg(const char* route,json::Value data ,bool isPush)
        : _data(data)
        , _isPush(isPush)
    {
        memset(_route,0x0,MAX_ROUTE_LEN);
        strncpy(_route,route,strlen(route));
    }
};

class PomeloConnection : public cocos2d::CCObject
{
public:
    PomeloConnection(IPomeloConnection& handler);
    ~PomeloConnection();

	int Connect(const char* ip,int port);

	int DoRequest(json::Value& reqJson,const char* route);
	int RegisterEvent(const char* route);

	void OnResponse(int reqId,json::Value res,const char* route);
	void OnEvent(const char* event,json::Value eventData);
	void OnClose();

    virtual void update(float dt);

    void AddPomeloMsg(const char* route,json::Value data ,bool isPush);

protected:
	struct pc_client_s *m_pClient;
	IPomeloConnection& m_protoHandler;

    std::list<PomeloMsg> m_msgList;

};
#endif