#pragma once
#include "BrakeType.h"
#include "CommonFunction.h"
#include <string>
class BrakeTypeFactory {
public:
    static IBrakeType *Create(const std::string & name);
    static IBrakeType *Create(int enum_no);
};

