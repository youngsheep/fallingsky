#ifndef _CONFIG_TESTCONFIGHOLDER_H_
#define _CONFIG_TESTCONFIGHOLDER_H_

#include "config/ConfigHolder.h"

struct TestConfig
{
    int id;
    std::string desc;
};

class TestConfigHolder : public ConfigHolder<TestConfig,int>
{
public:
    TestConfigHolder()
        : ConfigHolder<TestConfig,int>("test")
    {}

    virtual ~TestConfigHolder(){}

    virtual int ParseEntity(TestConfig& enti,const json::Value jsonEntity);
    virtual int getKey(TestConfig& enti){return enti.id;}

};
#endif