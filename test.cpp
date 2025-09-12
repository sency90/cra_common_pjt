#include "gmock/gmock.h"
#ifdef _WIN32
#pragma execution_character_set("utf-8")
#include <windows.h>
#endif

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <memory>

#include "CarAssembleApp.h"
#include "Enum.h"

using ::testing::Test;

class CarAssembleAppTestFixture : public Test{
protected:
    
    CarAssembleApp app;
    const int NONE_SETTING_TYPE{0};

    void SetSettings(
        int car_type,
        int engine_type,
        int brake_type,
        int steering_type
    ) {
        app.settings[PageEnum::eCarTypePage] = car_type;
        app.settings[PageEnum::eEnginePage] = engine_type;
        app.settings[PageEnum::eBrakePage] = brake_type;
        app.settings[PageEnum::eSteeringPage] = steering_type;
    }

    void SetUp() {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
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
TEST_F(CarAssembleAppTestFixture, ValidateInput_OnRunOrTestPage) {
    std::vector<std::string> exception_inputs = { "-1", "3" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eRunOrTestPage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = {"0", "1", "2"};
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eRunOrTestPage); });
    }
}
TEST_F(CarAssembleAppTestFixture, NotWorkingSedan) {
    SetSettings(eSedanCar, NONE_SETTING_TYPE, eCONTINENTALBrake, NONE_SETTING_TYPE);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(actual, "자동차가 동작되지 않습니다\n");
}

TEST_F(CarAssembleAppTestFixture, NotWorkingSUV) {
    SetSettings(eSUVCar, eTOYOTAEngine, NONE_SETTING_TYPE, NONE_SETTING_TYPE);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(actual, "자동차가 동작되지 않습니다\n");
}

TEST_F(CarAssembleAppTestFixture, NotWorkingTruck) {
    SetSettings(eTruckCar, eWIAEngine, NONE_SETTING_TYPE, NONE_SETTING_TYPE);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(actual, "자동차가 동작되지 않습니다\n");
}

TEST_F(CarAssembleAppTestFixture, NotWorkingTruck2) {
    SetSettings(eTruckCar, NONE_SETTING_TYPE, eMANDOBrake, NONE_SETTING_TYPE);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(actual, "자동차가 동작되지 않습니다\n");
}

TEST_F(CarAssembleAppTestFixture, NotWorkingTruck3) {
    SetSettings(eTruckCar, eWIAEngine, eMANDOBrake, NONE_SETTING_TYPE);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(actual, "자동차가 동작되지 않습니다\n");
}

TEST_F(CarAssembleAppTestFixture, NotWorkingBoschBrakeAndSteering) {
    SetSettings(NONE_SETTING_TYPE, NONE_SETTING_TYPE, eBOSCHBrake, eMOBISSteering);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ(actual, "자동차가 동작되지 않습니다\n");
}
TEST_F(CarAssembleAppTestFixture, NotWorkingBorkenEngine) {
    SetSettings(NONE_SETTING_TYPE, eBrokenEngine, NONE_SETTING_TYPE, NONE_SETTING_TYPE);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();
    std::string expected =
        "엔진이 고장나있습니다.\n"
        "자동차가 움직이지 않습니다.\n";
    EXPECT_EQ(actual, expected);
}

TEST_F(CarAssembleAppTestFixture, WorkingCar) {
    SetSettings(eSedanCar, eGMEngine, eMANDOBrake, eBOSCHSteering);

    ::testing::internal::CaptureStdout();
    app.RunProducedCar();
    std::string actual = ::testing::internal::GetCapturedStdout();

    std::stringstream ss;
    ss << "Car Type : " << app.CurrentCarTypeSettingToString() << "\n";
    ss << "Engine : " << app.CurrentEngineSettingToString() << "\n";
    ss << "Brake System : " << app.CurrentBrakeSettingToString() << "\n";
    ss << "SteeringSystem : " << app.CurrentSteeringSettingToString() << "\n";
    ss << "자동차가 동작됩니다.\n";

    std::string expected = ss.str();
    EXPECT_EQ(actual, expected);
}

