#ifndef _NET_GAME_PROTO_HANDLER_H_
#define _NET_GAME_PROTO_HANDLER_H_

#include <set>
#include "common/PomeloConnection.h"

class IGameProtoHandler
{
public:
    virtual void Response(std::string route,int result) = 0;
};

class GameProtoHandler : public IPomeloConnection 
{
public:
    static GameProtoHandler& GetInstance()
    {
        static GameProtoHandler inst;
        return inst;
    }
    virtual ~GameProtoHandler(){}

    virtual void ProtoHandlerCallback(json::Value& data,const char* route,bool isPush);

    void AddAllPushEvent();
    void RegisterProtoHandler(IGameProtoHandler* handler);
    void UnRegisterProtoHandler(IGameProtoHandler* handler);

    int ConnectGameSvr(const char* ip,int port);

    //loginRequest
    void DoLogin(const char* uid,const char* access_token);
    int OnLogin(json::Value data,const char* route);

    //battleRequest
    void StartBattleReq();
    int OnStartBattle(json::Value data,const char* route);
    void BattleCmdReq(int battleid,int xpos,int ypos,int flag);
    int OnBattleCmd(json::Value data,const char* route);

    //roleRequest
    void RoleCreateReq(const char* name);
    int OnRoleCreate(json::Value data,const char* route);
    void RoleInfoReq();
    int OnRoleInfo(json::Value data,const char* route);

    //push event
    int OnRoleBaseInfo(json::Value data,const char* route);
    int OnOppState(json::Value data,const char* route);

    bool IsWait(){return m_bWait;}
    void NeedWait(bool w){m_bWait = w;}

protected:
    GameProtoHandler()
        : m_pomeloConn(*this) 
        , m_bWait(false)
    {}

    void DoRequest(json::Value& req , std::string route,ProtoCallBack cb);
    void RemoveCallBack(std::string route);
    void AddPushEvent(std::string route, ProtoCallBack cb);

protected:
    std::map<std::string ,ProtoCallBack> m_protoCBMap;
    std::set<IGameProtoHandler*> m_uiHandlerSet;

private:
    PomeloConnection m_pomeloConn;
    bool m_bWait;
};
#endif