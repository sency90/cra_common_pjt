#include "gmock/gmock.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#include "CarAssembleApp.h"
#include "Enum.h"

using ::testing::Test;

class CarAssembleAppTestFixture : public Test{
protected:
    
    CarAssembleApp app;
    int settings[10];

    void SetSettings(
        CarEnum car_type,
        EngineEnum engine_type,
        BrakeEnum brake_type,
        SteeringEnum steering_type
    ) {
        settings[PageEnum::eCarTypePage] = car_type;
        settings[PageEnum::eEnginePage] = engine_type;
        settings[PageEnum::eBrakePage] = brake_type;
        settings[PageEnum::eSteeringPage] = steering_type;
    }
};

TEST_F(CarAssembleAppTestFixture, ValidateInput_WhenNotDigit) {
    std::string input = "a1";
    EXPECT_THROW({
    app.ValidateInput(input.c_str(), eCarTypePage);
        }, std::invalid_argument);
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_CarTypeNoOnCarTypePage) {
    std::vector<std::string> exception_inputs = { "0", "4" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eCarTypePage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = {"1", "2", "3"};
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eCarTypePage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_EngineTypeNoOnEnginePage) {
    std::vector<std::string> exception_inputs = { "-1", "5" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eEnginePage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = {"0", "1", "2", "3", "4"};
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eEnginePage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_BrakeTypeNoOnBrakePage) {
    std::vector<std::string> exception_inputs = { "-1", "4" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eBrakePage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = {"0", "1", "2", "3"};
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eBrakePage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_SteeringTypeNoOnSteeringPage) {
    std::vector<std::string> exception_inputs = { "-1", "3" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eSteeringPage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = {"0", "1", "2"};
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eSteeringPage); });
    }
}
