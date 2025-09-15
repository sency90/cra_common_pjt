#include "CarTypeFactory.h"
#include <cstring>

ICarType *CarTypeFactory::Create(int enum_no) {
    if(enum_no == eSedanCar) return new SedanCarType();
    else if(enum_no == eSUVCar) return new SuvCarType();
    else if(enum_no == eTruckCar) return new TruckCarType();
    else return new UnknownCarType();
}
