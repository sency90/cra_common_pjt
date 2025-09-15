#include "BrakeTypeFactory.h"

IBrakeType *BrakeTypeFactory::Create(int enum_no) {
    if(enum_no == eMANDOBrake) return new MandoBrakeType();
    else if(enum_no == eCONTINENTALBrake) return new ContinentalBrakeType();
    else if(enum_no == eBOSCHBrake) return new BoschBrakeType();
    else return new UnknownBrakeType();
}
