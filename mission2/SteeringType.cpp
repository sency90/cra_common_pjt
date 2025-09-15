#include "SteeringType.h"

const std::string BoschSteeringType::GetName() const {
    return "BOSCH";
}

const std::string MobisSteeringType::GetName() const {
    return "MOBIS";
}

const std::string UnknownSteeringType::GetName() const {
    return "";
}
