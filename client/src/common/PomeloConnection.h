#ifndef __FS_CONNECTION_H__
#define __FS_CONNECTION_H__

#include <map>
#include <string>

#define PROTO_MAGIC 1101

struct pc_client_s;
namespace json{
	class Value;
};

class ConnectObject;
class PomeloConnection
{
public:
	static PomeloConnection& getInstance();

	int Connect(const char* ip,int port);

	int DoRequest(ConnectObject* obj,const char* route);
	int RegisterEvent(ConnectObject* obj,const char* route);

	void OnResponse(int reqId,json::Value res);
	void OnEvent(const char* event,json::Value eventData);
	void OnClose();
protected:
	struct pc_client_s *m_pClient;
	
	std::map<int,ConnectObject*> m_ReqObjMap;
	std::map<std::string,ConnectObject*> m_EventObjMap;

private:
	PomeloConnection();
	~PomeloConnection();
};
#endif