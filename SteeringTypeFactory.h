#pragma once
#include "SteeringType.h"
#include "CommonFunction.h"
#include <string>
class SteeringTypeFactory {
public:
    static ISteeringType *Create(const std::string &name);
    static ISteeringType *Create(int enum_no);
};

