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

#ifndef CLEAR_SCREEN
#define CLEAR_SCREEN "\033[H\033[2J"
#endif

using ::testing::Test;

class MockCarAssembleApp: public CarAssembleApp {
public:
    MOCK_METHOD(char*, GetInput, (), (override));
};

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

TEST_F(CarAssembleAppTestFixture, PrintChoicePage1) {
    ::testing::internal::CaptureStdout();
    app.PrintChoicePage(eCarTypePage);
    std::string actual = ::testing::internal::GetCapturedStdout();

    std::stringstream ss;
    ss << CLEAR_SCREEN;
    ss << ("        ______________\n");
    ss << ("       /|            | \n");
    ss << ("  ____/_|_____________|____\n");
    ss << (" |                      O  |\n");
    ss << (" '-(@)----------------(@)--'\n");
    ss << ("===============================\n");
    ss << ("어떤 차량 타입을 선택할까요?\n");
    ss << ("1. Sedan\n");
    ss << ("2. SUV\n");
    ss << ("3. Truck\n");
    ss << ("===============================\n");
    
    std::string expected = ss.str();
    EXPECT_EQ(actual, expected);
}

TEST_F(CarAssembleAppTestFixture, PrintChoicePage2) {
    ::testing::internal::CaptureStdout();
    app.PrintChoicePage(eEnginePage);
    std::string actual = ::testing::internal::GetCapturedStdout();

    std::stringstream ss;
    ss << CLEAR_SCREEN;
    ss << ("어떤 엔진을 탑재할까요?\n");
    ss << ("0. 뒤로가기\n");
    ss << ("1. GM\n");
    ss << ("2. TOYOTA\n");
    ss << ("3. WIA\n");
    ss << ("4. 고장난 엔진\n");
    ss << ("===============================\n");
    
    std::string expected = ss.str();
    EXPECT_EQ(actual, expected);
}

TEST_F(CarAssembleAppTestFixture, PrintChoicePage3) {
    ::testing::internal::CaptureStdout();
    app.PrintChoicePage(eBrakePage);
    std::string actual = ::testing::internal::GetCapturedStdout();

    std::stringstream ss;
    ss << CLEAR_SCREEN;
    ss << ("어떤 제동장치를 선택할까요?\n");
    ss << ("0. 뒤로가기\n");
    ss << ("1. MANDO\n");
    ss << ("2. CONTINENTAL\n");
    ss << ("3. BOSCH\n");
    ss << ("===============================\n");
    
    std::string expected = ss.str();
    EXPECT_EQ(actual, expected);
}

TEST_F(CarAssembleAppTestFixture, PrintChoicePage4) {
    ::testing::internal::CaptureStdout();
    app.PrintChoicePage(eSteeringPage);
    std::string actual = ::testing::internal::GetCapturedStdout();

    std::stringstream ss;
    ss << CLEAR_SCREEN;
    ss << ("어떤 조향장치를 선택할까요?\n");
    ss << ("0. 뒤로가기\n");
    ss << ("1. BOSCH\n");
    ss << ("2. MOBIS\n");
    ss << ("===============================\n");
    
    std::string expected = ss.str();
    EXPECT_EQ(actual, expected);
}

TEST_F(CarAssembleAppTestFixture, PrintChoicePage5) {
    ::testing::internal::CaptureStdout();
    app.PrintChoicePage(eRunOrTestPage);
    std::string actual = ::testing::internal::GetCapturedStdout();

    std::stringstream ss;
    ss << CLEAR_SCREEN;
    ss << ("멋진 차량이 완성되었습니다.\n");
    ss << ("어떤 동작을 할까요?\n");
    ss << ("0. 처음 화면으로 돌아가기\n");
    ss << ("1. RUN\n");
    ss << ("2. Test\n");
    ss << ("===============================\n");
    
    std::string expected = ss.str();
    EXPECT_EQ(actual, expected);
}
