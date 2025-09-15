#pragma once
#include "BrakeType.h"
#include "CommonFunction.h"
#include <string>

enum BrakeEnum {
    eMANDOBrake=1,
    eCONTINENTALBrake,
    eBOSCHBrake
};

class BrakeTypeFactory {
public:
    static up<IBrakeType> Create(int enum_no);
};

