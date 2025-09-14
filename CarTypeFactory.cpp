#include "CarTypeFactory.h"
#include "Enum.h"
#include <cstring>

ICarType *CarTypeFactory::Create(const std::string &name) {
    CommonFunction &cf = CommonFunction::GetInstance();
    const std::string lower_name = cf.ToLower(name);
    if(lower_name == "sedan") return new SedanCarType();
    else if(lower_name == "suv") return new SuvCarType();
    else if(lower_name == "truck") return new TruckCarType();
    else return new UnknownCarType();
}

ICarType *CarTypeFactory::Create(int enum_no) {
    if(enum_no == eSedanCar) return new SedanCarType();
    else if(enum_no == eSUVCar) return new SuvCarType();
    else if(enum_no == eTruckCar) return new TruckCarType();
    else return new UnknownCarType();
}
