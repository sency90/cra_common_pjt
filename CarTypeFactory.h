#pragma once
#include "CarType.h"
#include "CommonFunction.h"
#include <string>

enum CarEnum {
    eSedanCar=1,
    eSUVCar,
    eTruckCar
};

class CarTypeFactory {
public:
    static ICarType *Create(const std::string &name);
    static ICarType *Create(int enum_no);
};

