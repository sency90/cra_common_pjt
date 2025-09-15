#include "BrakeType.h"

const std::string MandoBrakeType::GetName() const {
    return "MANDO";
}

const std::string ContinentalBrakeType::GetName() const {
    return "CONTINENTAL";
}

const std::string BoschBrakeType::GetName() const {
    return "BOSCH";
}

const std::string UnknownBrakeType::GetName() const {
    return "";
}
