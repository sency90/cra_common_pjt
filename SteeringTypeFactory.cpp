#include "SteeringTypeFactory.h"

up<ISteeringType> SteeringTypeFactory::Create(int enum_no) {
    if(enum_no == eBOSCHSteering) return make_up<BoschSteeringType>();
    else if(enum_no == eMOBISSteering) return make_up<MobisSteeringType>();
    else return make_up<UnknownSteeringType>();
}
