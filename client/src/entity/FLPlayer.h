//
//  FLPlayer.h
//  HelloCpp
//
//  Created by yy on 14-5-9.
//
//

#ifndef __Entity__FLPlayer__
#define __Entity__FLPlayer__

#include "common/jansson.hpp"
#include "FLBattle.h"

#define MAX_NICKNAME_LEN 128
#define MAX_PORTRAIT_LEN 128
#define MAX_TOKEN_LEN 128

class FLPlayer 
{
public:
    static FLPlayer& GetInstance()
    {
        static FLPlayer inst;
        return inst;
    }

    ~FLPlayer(){}
    
    void InitBaseInfo(json::Value& data);

    int GetPlayerID(){return m_pid;}
    void SetPlayerID(int id){m_pid = id;}

    const char* GetUid(){return m_uid;}
    void SetUid(const char* uid);
    const char* GetNickName(){return m_nickname;}
    void SetNickName(const char* name);
    const char* GetPortrait(){return m_portrait;}
    void SetPortrait(const char* p);
    const char* GetWeiboToken(){return m_weiboToken;}
    void SetWeiboToken(const char* t);
    
    FLBattle& GetBattle(){return m_battle;}
protected:
    int m_pid;
    char m_uid[MAX_USERNAME_LEN];
    char m_nickname[MAX_NICKNAME_LEN];
    char m_portrait[MAX_PORTRAIT_LEN];
    char m_weiboToken[MAX_TOKEN_LEN];
    
    FLBattle m_battle;

private:
    FLPlayer();
};

#endif /* defined(__Entity__FLPlayer__) */
