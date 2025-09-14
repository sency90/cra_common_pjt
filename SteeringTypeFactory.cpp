#include "SteeringTypeFactory.h"
#include "Enum.h"

ISteeringType *SteeringTypeFactory::Create(const std::string &name) {
    CommonFunction &cf = CommonFunction::GetInstance();
    if(name == "BOSCH") return new BoschSteeringType();
    else if(name == "MOBIS") return new MobisSteeringType();
    else return new UnknownSteeringType();
}

ISteeringType *SteeringTypeFactory::Create(int enum_no) {
    if(enum_no == eBOSCHSteering) return new BoschSteeringType();
    else if(enum_no == eMOBISSteering) return new MobisSteeringType();
    else return new UnknownSteeringType();
}
