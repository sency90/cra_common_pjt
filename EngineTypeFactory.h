#pragma once
#include "EngineType.h"
#include "CommonFunction.h"
#include <string>

enum EngineEnum {
    eGMEngine=1,
    eTOYOTAEngine,
    eWIAEngine,
    eBrokenEngine
};

class EngineTypeFactory {
public:
    static up<IEngineType> Create(int enum_no);
};

