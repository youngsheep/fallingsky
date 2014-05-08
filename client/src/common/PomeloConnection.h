#ifndef __FS_CONNECTION_H__
#define __FS_CONNECTION_H__

#include <map>
#include <string>

#define PROTO_MAGIC 1101

struct pc_client_s;
namespace json{
	class Value;
};

class RequestDeletegate;
class PushEventListener;
class PomeloConnection
{
public:
	static PomeloConnection& getInstance();

	int Connect(const char* ip,int port);

	int DoRequest(RequestDeletegate* obj,json::Value& reqJson,const char* route);
	int RegisterEvent(PushEventListener* obj,const char* route);

	void OnResponse(int reqId,json::Value res,const char* route);
	void OnEvent(const char* event,json::Value eventData);
	void OnClose();
protected:
	struct pc_client_s *m_pClient;
	
	std::map<int,RequestDeletegate*> m_ReqObjMap;
	std::map<std::string,PushEventListener*> m_EventObjMap;

private:
	PomeloConnection();
	~PomeloConnection();
};
#endif