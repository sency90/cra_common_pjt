#include "CarType.h"

const std::string SedanCarType::GetName() const {
    return "Sedan";
}

const std::string SuvCarType::GetName() const {
    return "SUV";
}

const std::string TruckCarType::GetName() const {
    return "Truck";
}

const std::string UnknownCarType::GetName() const {
    return "";
}
