#include "GameProtoHandler.h"

void GameProtoHandler::ProtoHandlerCallback(json::Value& data,const char* route,bool isPush)
{
    std::map<std::string,ProtoCallBack>::iterator itor = m_protoCBMap.find(route);
    if (itor != m_protoCBMap.end())
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

    m_protoCBMap.insert(std::make_pair(route,cb));
}

void GameProtoHandler::RemoveCallBack(std::string route)
{
    std::map<std::string,ProtoCallBack>::iterator itor = m_protoCBMap.find(route);
    if (itor != m_protoCBMap.end())
    {
        m_protoCBMap.erase(itor);
    }
}

void GameProtoHandler::AddPushEvent(std::string route,ProtoCallBack cb)
{
    m_pomeloConn.RegisterEvent(route.c_str());
    m_protoCBMap.insert(std::make_pair(route,cb));
}

void GameProtoHandler::AddAllPushEvent()
{
    AddPushEvent("roleBaseInfo",pomelo_selector(GameProtoHandler::OnRoleBaseInfo));
    AddPushEvent("game.battleHandler.start",pomelo_selector(GameProtoHandler::OnStartBattle));
    AddPushEvent("oppstate",pomelo_selector(GameProtoHandler::OnOppState));
}

void GameProtoHandler::RegisterProtoHandler(IGameProtoHandler* handler)
{
    m_uiHandlerSet.insert(handler);
}

void GameProtoHandler::UnRegisterProtoHandler(IGameProtoHandler* handler)
{
    m_uiHandlerSet.erase(handler);
}
