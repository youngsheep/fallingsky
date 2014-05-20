#ifndef _NET_GAME_PROTO_HANDLER_H_
#define _NET_GAME_PROTO_HANDLER_H_

#include "common/PomeloConnection.h"

class IGameProtoHandler
{
    virtual void Response(std::string route,int result);
};

class GameProtoHandler : public IPomeloConnection 
{
    typedef void (GameProtoHandler::*ProtoCallBack)(json::Value data,const char* route);
public:
    static GameProtoHandler& GetInstance()
    {
        static GameProtoHandler inst;
        return inst;
    }
    virtual ~GameProtoHandler(){}

    virtual void RequestCallback(json::Value& data,const char* route);
    virtual void PushCallback(json::Value& data,const char* route);

    void AddAllPushEvent();
    void RegisterProtoHandler(IGameProtoHandler* handler);
    void UnRegisterProtoHandler(IGameProtoHandler* handler);

    int ConnectGameSvr(const char* ip,int port);

    //loginRequest
    void DoLogin(const char* name);
    void OnLogin(json::Value data,const char* route);

    //battleRequest
    void StartBattleReq();
    void OnStartBattle(json::Value data,const char* route);
    void BattleCmdReq(int battleid,int xpos,int ypos,int flag);
    void OnBattleCmd(json::Value data,const char* route);

    //roleRequest
    void RoleCreateReq(const char* name);
    void OnRoleCreate(json::Value data,const char* route);
    void RoleInfoReq();
    void OnRoleInfo(json::Value data,const char* route);

    //push event
    void OnRoleBaseInfo(json::Value data,const char* route);
    void OnOppState(json::Value data,const char* route);

    bool IsWait(){return m_bWait;}
    void NeedWait(bool w){m_bWait = w;}

protected:
    GameProtoHandler()
        : m_pomeloConn(*this) 
        , m_bWait(false)
    {}

    void DoRequest(json::Value& req , std::string route,ProtoCallBack cb);
    void RemoveRequest(std::string route);
    void AddPushEvent(std::string route, ProtoCallBack cb);
    void RemovePushEvent(std::string route);

protected:
    std::map<std::string ,ProtoCallBack> m_reqCBMap;
    std::map<std::string ,ProtoCallBack> m_pushCBMap;

private:
    PomeloConnection m_pomeloConn;
    bool m_bWait;
};
#endif