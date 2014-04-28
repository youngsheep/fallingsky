#ifndef _CONFIG_CONFIGHOLDER_H_
#define _CONFIG_CONFIGHOLDER_H_

#include <vector>
#include <map>
#include <string>


#include "common/jansson.hpp"
#include "pomelo-protobuf/pb.h"

template<class Entity, typename KeyType>
class ConfigHolder
{
public:
    ConfigHolder(const char* name,const char* proto)
        : m_szEntityName(name)
        , m_szProto(proto)
    {}
    virtual ~ConfigHolder(){}

    virtual int ParseEntity(Entity& enti,const json::Value jsonEntity) = 0;
    virtual KeyType getKey(Entity& enti) = 0;

    const Entity& getEntityByIdx(int idx)
    {
        return m_ConfigVec[idx];
    }

    const Entity& getEntityByKey(KeyType key)
    {
        int idx = m_ConfigMap[key];
        return m_ConfigVec[idx];
    }

    void LoadConfig();


protected:
    std::vector<Entity> m_ConfigVec;
    std::map<KeyType,int> m_ConfigMap;

    const char* m_szEntityName;
    const char* m_szProto;
};

#include "ConfigHolder.hpp"

#endif

