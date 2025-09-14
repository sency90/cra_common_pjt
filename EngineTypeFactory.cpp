#include "EngineTypeFactory.h"
#include "Enum.h"

IEngineType *EngineTypeFactory::Create(const std::string &name) {
    CommonFunction &cf = CommonFunction::GetInstance();
    const std::string lower_name = cf.ToLower(name);
    if(lower_name == "gm") return new GmEngineType();
    else if(lower_name == "toyota") return new ToyotaEngineType();
    else if(lower_name == "wia") return new WiaEngineType();
    else if(lower_name == "broken") return new BrokenEngineType();
    else return new UnknownEngineType();
}

IEngineType *EngineTypeFactory::Create(int enum_no) {
    if(enum_no == eGMEngine) return new GmEngineType();
    else if(enum_no == eTOYOTAEngine) return new ToyotaEngineType();
    else if(enum_no == eWIAEngine) return new WiaEngineType();
    else if(enum_no == eBrokenEngine) return new BrokenEngineType();
    else return new UnknownEngineType();
}
