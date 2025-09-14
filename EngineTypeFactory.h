#pragma once
#include "EngineType.h"
#include "CommonFunction.h"
#include <string>
class EngineTypeFactory {
public:
    static IEngineType *Create(const std::string &name);
    static IEngineType *Create(int enum_no);
};

