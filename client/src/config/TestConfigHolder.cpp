#include "TestConfigHolder.h"
#include "common/jansson.hpp"

int TestConfigHolder::ParseEntity(TestConfig& enti,const json::Value jsonEntity) 
{
    enti.id = jsonEntity["id"].as_integer();
    enti.desc = jsonEntity["desc"].as_string();
         
    return 0;
}
