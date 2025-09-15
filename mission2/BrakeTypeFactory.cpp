#include "BrakeTypeFactory.h"

up<IBrakeType> BrakeTypeFactory::Create(int enum_no) {
    if(enum_no == eMANDOBrake) return make_up<MandoBrakeType>();
    else if(enum_no == eCONTINENTALBrake) return make_up<ContinentalBrakeType>();
    else if(enum_no == eBOSCHBrake) return make_up<BoschBrakeType>();
    else return make_up<UnknownBrakeType>();
}
