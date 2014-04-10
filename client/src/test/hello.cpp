#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "pomelo.h"

#define MAX_LINE_CHARS 2

#define END_STR "bye"

const int MAX_REQUEST_COUNT = 3;
const char* request_str[MAX_REQUEST_COUNT] = {
	"connector.entryHandler.entry",
	"match.randomHandler.match",
	"bye"
};

const char *ip = "127.0.0.1";
int port = 3010;

// request callback
void on_request_cb(pc_request_t *req, int status, json_t *resp) {
  if(status == -1) {
    printf("Fail to send request to server.\n");
  } else if(status == 0) {
    printf("server echo: %s\n",
           json_string_value(resp));
  }

  // release relative resource with pc_request_t
  json_t *msg = req->msg;
  json_decref(msg);
  pc_request_destroy(req);
}

void do_request(pc_client_t *client, const char *route,const char* input,pc_request_cb cb) {
  // compose request
  json_t *msg = json_object();
  json_t *str = json_string(input);
  json_object_set(msg, "body", str);
  // decref for json object
  json_decref(str);

  pc_request_t *request = pc_request_new();
  pc_request(client, request, route, msg, cb);
}

// disconnect event callback.
void on_close(pc_client_t *client, const char *event, void *data) {
  printf("client closed: %d.\n", client->state);
}

void on_login(pc_request_t *req, int status, json_t *resp)  {
	uint32_t result = json_integer_value(json_object_get(resp, "result"));
	int playerid = json_integer_value(json_object_get(resp, "playerid"));
	printf("server on_login -- result:%d   playerid:%d\n",result,playerid);
}
 
void on_match(pc_request_t *req, int status, json_t *resp) {
	int result = json_integer_value(json_object_get(resp, "result"));
	int matchid = json_integer_value(json_object_get(resp, "matchid"));
	printf("server on_match -- result:%d   matchid:%d\n",result,matchid	);
}

void on_match_event(pc_client_t *client, const char *event, void *data)  {
	int result = json_integer_value(json_object_get((json_t*)data, "result"));
	int matchid = json_integer_value(json_object_get((json_t*)data, "matchid"));
	printf("server on_match_event -- result:%d   matchid:%d\n",result,matchid	);
}

pc_request_cb resp_cb[MAX_REQUEST_COUNT] = {
	on_login,
	on_match,
	on_login
};

int hand_shake_cb(pc_client_t *client, json_t *msg)
{
	json_t *clientEntry = json_object_get((json_t*)client->client_protos, "connector.entryHandler.entry");
	
	return 0;
}

int main() {
  // create a client instance.
  pc_client_t *client = pc_client_new();
  client->handshake_cb = hand_shake_cb;

  struct sockaddr_in address;

  memset(&address, 0, sizeof(struct sockaddr_in));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip);

  // add some event callback.
  pc_add_listener(client, PC_EVENT_DISCONNECT, on_close);
  pc_add_listener(client, "match.randomHandler.match", on_match_event);

  // try to connect to server.
  if(pc_client_connect(client, &address)) {
    printf("fail to connect server.\n");
    pc_client_destroy(client);
    return 1;
  }

  int maxChoice = sizeof(request_str)/sizeof(const char*);
  char input[MAX_LINE_CHARS];

  printf("Input a line to send message to server and input `bye` to exit.\n");
  while(1) {
	printf("Command: \n");
	for (int i = 0;i < maxChoice; i++)
	{
		printf("%d : %s \n" ,i,request_str[i]);
	}	

    scanf("%s", input);
	if (input[0] < '0' || input[0] > '9')
	{
		continue;
	}
	
	int idx = input[0] - '0';
    if(!strcmp(request_str[idx], END_STR)) {
      break;
    }

    do_request(client, request_str[idx] , request_str[idx],resp_cb[idx]);
  }

  // release the client
  pc_client_destroy(client);

  return 0;
}
