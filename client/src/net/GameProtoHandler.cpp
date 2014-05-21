#include "GameProtoHandler.h"

void GameProtoHandler::RequestCallback(json::Value& data,const char* route)
{
    std::map<std::string,ProtoCallBack>::iterator itor = m_reqCBMap.find(route);
    if (itor != m_reqCBMap.end())
    {
        int result = (this->*(itor->second))(data, route);
        for (std::set<IGameProtoHandler*>::iterator it = m_uiHandlerSet.begin(); it != m_uiHandlerSet.end(); it++) {
            (*it)->Response(route, result);
        }
    }
}

void GameProtoHandler::PushCallback(json::Value& data,const char* route)
{
    std::map<std::string,ProtoCallBack>::iterator itor = m_pushCBMap.find(route);
    if (itor != m_pushCBMap.end())
    {
        int result = (this->*(itor->second))(data, route);
        for (std::set<IGameProtoHandler*>::iterator it = m_uiHandlerSet.begin(); it != m_uiHandlerSet.end(); it++) {
            (*it)->Response(route, result);
        }
    }
}

int GameProtoHandler::ConnectGameSvr(const char* ip,int port)
{
    return m_pomeloConn.Connect(ip,port);
}

void GameProtoHandler::DoRequest(json::Value& req , std::string route,ProtoCallBack cb)
{
    m_pomeloConn.DoRequest(req,route.c_str());

    m_reqCBMap.insert(std::make_pair(route,cb));
    NeedWait(true);
}

void GameProtoHandler::RemoveRequest(std::string route)
{
    std::map<std::string,ProtoCallBack>::iterator itor = m_reqCBMap.find(route);
    if (itor != m_reqCBMap.end())
    {
        m_reqCBMap.erase(itor);
    }
    NeedWait(false);
}

void GameProtoHandler::AddPushEvent(std::string route,ProtoCallBack cb)
{
    m_pomeloConn.RegisterEvent(route.c_str());
    m_pushCBMap.insert(std::make_pair(route,cb));
}

void GameProtoHandler::RemovePushEvent(std::string route)
{
    std::map<std::string,ProtoCallBack>::iterator itor = m_pushCBMap.find(route);
    if (itor != m_pushCBMap.end())
    {
        m_pushCBMap.erase(itor);
    }
}

void GameProtoHandler::AddAllPushEvent()
{
    AddPushEvent("roleBaseInfo",&GameProtoHandler::OnRoleBaseInfo);
    AddPushEvent("game.battleHandler.start",&GameProtoHandler::OnStartBattle);
    AddPushEvent("oppstate",&GameProtoHandler::OnOppState);
}

void GameProtoHandler::RegisterProtoHandler(IGameProtoHandler* handler)
{
    m_uiHandlerSet.insert(handler);
}

void GameProtoHandler::UnRegisterProtoHandler(IGameProtoHandler* handler)
{
    m_uiHandlerSet.erase(handler);
}
