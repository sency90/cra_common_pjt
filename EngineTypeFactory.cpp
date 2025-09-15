#include "EngineTypeFactory.h"

IEngineType *EngineTypeFactory::Create(int enum_no) {
    if(enum_no == eGMEngine) return new GmEngineType();
    else if(enum_no == eTOYOTAEngine) return new ToyotaEngineType();
    else if(enum_no == eWIAEngine) return new WiaEngineType();
    else if(enum_no == eBrokenEngine) return new BrokenEngineType();
    else return new UnknownEngineType();
}
