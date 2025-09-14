#include "BrakeTypeFactory.h"
#include "Enum.h"

IBrakeType *BrakeTypeFactory::Create(const std::string &name) {
    CommonFunction &cf = CommonFunction::GetInstance();
    const std::string lower_name = cf.ToLower(name);
    if(lower_name == "mando") return new MandoBrakeType();
    else if(lower_name == "continental") return new ContinentalBrakeType();
    else if(lower_name == "bosch") return new BoschBrakeType();
    else return new UnknownBrakeType();
}

IBrakeType *BrakeTypeFactory::Create(int enum_no) {
    if(enum_no == eMANDOBrake) return new MandoBrakeType();
    else if(enum_no == eCONTINENTALBrake) return new ContinentalBrakeType();
    else if(enum_no == eBOSCHBrake) return new BoschBrakeType();
    else return new UnknownBrakeType();
}
