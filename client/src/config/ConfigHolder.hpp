#include "platform/CCFileUtils.h"

USING_NS_CC;

template<class Entity, typename KeyType>
void ConfigHolder<Entity,KeyType>::LoadConfig()
{
    json::Value data(json::object());

    std::string resName = std::string("res_")+ m_szEntityName +".bin";
    unsigned long resLen = 0;
    unsigned char* res = CCFileUtils::sharedFileUtils()->getFileData(resName.c_str(),"r",&resLen);

    json::Value proto(json::load_string(m_szProto));
    if (proto.is_object())
    {
        printf("proto : %s \n",proto.save_string());

        json::Value pbdef= proto[m_szEntityName].as_json();
        if (pbdef.is_object() && data.is_object())
        {
            printf("pbdef : %s \n",pbdef.save_string());

            if (!pc_pb_decode(res, resLen,
                proto.as_json(), pbdef.as_json(), data.as_json())) {
                    printf("Fail to do protobuf decode.\n");
            }
        }
    }

    printf("data is %s\n",data.save_string());

    const json::Value dataArr = data[m_szEntityName].as_json();
    if (dataArr.is_array())
    {
        int size = dataArr.size();
        for (int i = 0 ; i < size ; i++)
        {
            const json::Value entity = dataArr.at(i);
            if(entity.is_object())
            {
                Entity conf;
                ParseEntity(conf,entity);

                m_ConfigVec.push_back(conf);
                m_ConfigMap[getKey(conf)] = m_ConfigVec.size() - 1;
            }
        }
    }

    delete[] res;
}
