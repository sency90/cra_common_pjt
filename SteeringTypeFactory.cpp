#include "SteeringTypeFactory.h"

ISteeringType *SteeringTypeFactory::Create(int enum_no) {
    if(enum_no == eBOSCHSteering) return new BoschSteeringType();
    else if(enum_no == eMOBISSteering) return new MobisSteeringType();
    else return new UnknownSteeringType();
}
