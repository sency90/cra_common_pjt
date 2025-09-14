#include "EngineType.h"

const std::string GmEngineType::GetName() const {
    return "GM";
}

const std::string ToyotaEngineType::GetName() const {
    return "TOYOTA";
}

const std::string WiaEngineType::GetName() const {
    return "WIA";
}

const std::string BrokenEngineType::GetName() const {
    return "BROKEN";
}

const std::string UnknownEngineType::GetName() const {
    return "";
}
