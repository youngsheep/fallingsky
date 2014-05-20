#ifndef __FS_CONNECTION_H__
#define __FS_CONNECTION_H__

#include <map>
#include <string>
#include "jansson.hpp"

#define PROTO_MAGIC 1101
#define MAX_ROUTE_LEN 128

struct pc_client_s;
class IPomeloConnection
{
public:
    virtual void RequestCallback(json::Value& data,const char* route) = 0;
    virtual void PushCallback(json::Value& data,const char* route) = 0;
};

class PomeloConnection
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
protected:
	struct pc_client_s *m_pClient;
	IPomeloConnection& m_protoHandler;

};
#endif