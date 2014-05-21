//
//  FLPlayer.cpp
//  HelloCpp
//
//  Created by yy on 14-5-9.
//
//

#include "FLPlayer.h"

FLPlayer::FLPlayer()
{

}

void FLPlayer::InitBaseInfo(json::Value& data)
{

}

void FLPlayer::SetUid(const char* uid)
{
    int len = strlen(uid);
    len = len > MAX_USERNAME_LEN ? MAX_USERNAME_LEN : len ;
    strncpy(m_uid,uid,len);
}

void FLPlayer::SetNickName(const char* name)
{
    int len = strlen(name);
    len = len > MAX_NICKNAME_LEN ? MAX_NICKNAME_LEN : len ;
    strncpy(m_nickname,name,len);
}

void FLPlayer::SetPortrait(const char* p)
{
    int len = strlen(p);
    len = len > MAX_PORTRAIT_LEN ? MAX_PORTRAIT_LEN : len ;
    strncpy(m_portrait,p,len);
}
