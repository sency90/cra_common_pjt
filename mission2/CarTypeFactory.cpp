#include "CarTypeFactory.h"
#include <cstring>

up<ICarType> CarTypeFactory::Create(int enum_no) {
    if(enum_no == eSedanCar) return make_up<SedanCarType>();
    else if(enum_no == eSUVCar) return make_up<SuvCarType>();
    else if(enum_no == eTruckCar) return make_up<TruckCarType>();
    else return make_up<UnknownCarType>();
}
