#pragma once
#include "SteeringType.h"
#include "CommonFunction.h"
#include <string>

enum SteeringEnum {
    eBOSCHSteering=1,
    eMOBISSteering
};

class SteeringTypeFactory {
public:
    static ISteeringType *Create(int enum_no);
};

