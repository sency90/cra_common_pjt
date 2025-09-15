#include "EngineTypeFactory.h"

up<IEngineType> EngineTypeFactory::Create(int enum_no) {
    if(enum_no == eGMEngine) return make_up<GmEngineType>();
    else if(enum_no == eTOYOTAEngine) return make_up<ToyotaEngineType>();
    else if(enum_no == eWIAEngine) return make_up<WiaEngineType>();
    else if(enum_no == eBrokenEngine) return make_up<BrokenEngineType>();
    else return make_up<UnknownEngineType>();
}
