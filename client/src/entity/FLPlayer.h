//
//  FLPlayer.h
//  HelloCpp
//
//  Created by yy on 14-5-9.
//
//

#ifndef __Entity__FLPlayer__
#define __Entity__FLPlayer__

#define MAX_NICKNAME_LEN 128
#define MAX_PORTRAIT_LEN 128

class FLPlayer 
{
public:
    FLPlayer()
    {}
    ~FLPlayer();
    
    void InitBaseInfo(json::Value& data);

protected:
    int m_uid;
    char m_username[MAX_USERNAME_LEN];
    char m_nickname[MAX_NICKNAME_LEN];
    char m_portrait[MAX_PORTRAIT_LEN];

    FLBattle m_battle;
};

#endif /* defined(__Entity__FLPlayer__) */
