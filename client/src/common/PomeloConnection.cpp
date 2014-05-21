#include "PomeloConnection.h"
#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#include "pomelo.h"

static std::map<pc_client_t*,PomeloConnection*> s_connMap;

PomeloConnection* get_conn(pc_client_t* client)
{
    std::map<pc_client_t*,PomeloConnection*>::iterator itor = s_connMap.find(client);
    if (itor != s_connMap.end())
    {
        return itor->second;
    }
    return NULL;
}

void on_response(pc_request_t *req, int status, json_t *resp)  {
    PomeloConnection* conn = get_conn(req->client);
    if (conn)
    {
	    conn->OnResponse(req->id,json::Value(resp),req->route);
    }
	
	// release relative resource with pc_request_t
    json_t *msg = req->msg;
    json_decref(msg);
	pc_request_destroy(req);
}

void on_push_event(pc_client_t *client, const char *event, void *data) {
    PomeloConnection* conn = get_conn(client);
    if (conn)
    {
        conn->OnEvent(event,json::Value((json_t*)data));
    }
}

int hand_shake(pc_client_t *client, json_t *msg)
{
	printf("hand shake success.\n");
	return 0;
}

void on_conn_close(pc_client_t *client, const char *event, void *data) {
	printf("client closed: %d.\n", client->state);
    PomeloConnection* conn = get_conn(client);
    if (conn)
    {
        conn->OnClose();
    }
}

PomeloConnection::PomeloConnection(IPomeloConnection& handler)
    : m_protoHandler(handler)
{
	m_pClient = pc_client_new();
	m_pClient->handshake_cb = hand_shake;

    s_connMap.insert(std::make_pair(m_pClient,this));

	// add some event callback.
	pc_add_listener(m_pClient, PC_EVENT_DISCONNECT, on_conn_close);
	pc_add_listener(m_pClient, PC_EVENT_TIMEOUT, on_conn_close);
	pc_add_listener(m_pClient, PC_EVENT_KICK, on_conn_close);
}

PomeloConnection::~PomeloConnection()
{
    std::map<pc_client_t*,PomeloConnection*>::iterator itor = s_connMap.find(m_pClient);
    if (itor != s_connMap.end())
    {
        s_connMap.erase(itor);
    }
	pc_client_destroy(m_pClient);
}

int PomeloConnection::Connect(const char* ip,int port)
{
	struct sockaddr_in address;
	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip);

	// try to connect to server.
	if(pc_client_connect(m_pClient, &address)) {
		printf("fail to connect server.\n");
		return -1;
	}
	return 0;
}

int PomeloConnection::DoRequest(json::Value& reqJson,const char* route)
{
	pc_request_t *request = pc_request_new();
    request->data = (void*)this;
    json_t* req = json_incref(reqJson.as_json());
	pc_request(m_pClient, request, route, req, on_response);
	return 0;
}

int PomeloConnection::RegisterEvent(const char* route)
{
	pc_add_listener(m_pClient, route, on_push_event);
	return 0;
}

void PomeloConnection::OnResponse(int reqId,json::Value res,const char* route)
{
    const char* str = res.save_string();
    printf("%s |  data : %s  \n" , route, str);
    free((void*)str);

	m_protoHandler.RequestCallback(res,route);
}

void PomeloConnection::OnEvent(const char* event,json::Value eventData)
{
	m_protoHandler.PushCallback(eventData,event);
}

void PomeloConnection::OnClose()
{

}

