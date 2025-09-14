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
using ::testing::InSequence;
using ::testing::Return;
using ::testing::HasSubstr;

struct ExitCalled: public std::exception {};

class MockCarAssembleApp: public CarAssembleApp {
public:
    MOCK_METHOD(char *, GetInput, (), (override));

    void ExitProgram() override {
        printf("바이바이\n");
        throw ExitCalled{};
    }
};

class CarAssembleAppTestFixture: public Test {
protected:

    CarAssembleApp app;
    const int NONE_SETTING_TYPE{ 0 };

    void SetSettings(
        int car_type,
        int engine_type,
        int brake_type,
        int steering_type
    ) {
        app.car_type = CarTypeFactory::Create(car_type);
        app.engine_type = EngineTypeFactory::Create(engine_type);
        app.brake_type = BrakeTypeFactory::Create(brake_type);
        app.steering_type = SteeringTypeFactory::Create(steering_type);
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

    std::vector<std::string> normal_inputs = { "1", "2", "3" };
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eCarTypePage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_EngineTypeNoOnEnginePage) {
    std::vector<std::string> exception_inputs = { "-1", "5" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eEnginePage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = { "0", "1", "2", "3", "4" };
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eEnginePage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_BrakeTypeNoOnBrakePage) {
    std::vector<std::string> exception_inputs = { "-1", "4" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eBrakePage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = { "0", "1", "2", "3" };
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eBrakePage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_SteeringTypeNoOnSteeringPage) {
    std::vector<std::string> exception_inputs = { "-1", "3" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eSteeringPage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = { "0", "1", "2" };
    for(auto input : normal_inputs) {
        EXPECT_NO_THROW({ app.ValidateInput(input.c_str(), eSteeringPage); });
    }
}
TEST_F(CarAssembleAppTestFixture, ValidateInput_OnRunOrTestPage) {
    std::vector<std::string> exception_inputs = { "-1", "3" };
    for(auto input : exception_inputs) {
        EXPECT_THROW({ app.ValidateInput(input.c_str(), eRunOrTestPage); }, std::invalid_argument);
    }

    std::vector<std::string> normal_inputs = { "0", "1", "2" };
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
    ss << "Car Type : " << app.car_type->GetName() << "\n";
    ss << "Engine : " << app.engine_type->GetName() << "\n";
    ss << "Brake System : " << app.brake_type->GetName() << "\n";
    ss << "SteeringSystem : " << app.steering_type->GetName() << "\n";
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

TEST_F(CarAssembleAppTestFixture, ExitImmediately_PrintsByeAndStops) {
    MockCarAssembleApp app;

    static char s_exit[5] = "exit";
    EXPECT_CALL(app, GetInput()).WillOnce(Return(s_exit));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW({ app.Run(); }, ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, FullFlow_TestPass_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    // Sedan(1) → GM(1) → MANDO(1) → BOSCH(1) → Test(2) → exit
    static char s1[] = "1";
    static char s2[] = "1";
    static char s3[] = "1";
    static char s4[] = "1";
    static char s5[] = "2";
    static char s6[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s1))
        .WillOnce(Return(s2))
        .WillOnce(Return(s3))
        .WillOnce(Return(s4))
        .WillOnce(Return(s5))
        .WillOnce(Return(s6));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("자동차 부품 조합 테스트 결과 : PASS"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, InvalidInput_ShowsError_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    static char s_bad[]  = "a1";
    static char s_exit[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s_bad))
        .WillOnce(Return(s_exit));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("ERROR :: 숫자만 입력 가능"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, FullFlow_TestFail_SedanContinentalBrake_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    static char s1[] = "1"; //sedan
    static char s2[] = "1";
    static char s3[] = "2"; //continental
    static char s4[] = "1";
    static char s5[] = "2";
    static char s6[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s1))
        .WillOnce(Return(s2))
        .WillOnce(Return(s3))
        .WillOnce(Return(s4))
        .WillOnce(Return(s5))
        .WillOnce(Return(s6));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("자동차 부품 조합 테스트 결과 : FAIL"));
    EXPECT_THAT(out, HasSubstr("Sedan에는 Continental제동장치 사용 불가"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, FullFlow_TestFail_SuvToyotaEngine_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    static char s1[] = "2"; //SUV
    static char s2[] = "2"; //Toyota
    static char s3[] = "1";
    static char s4[] = "1";
    static char s5[] = "2";
    static char s6[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s1))
        .WillOnce(Return(s2))
        .WillOnce(Return(s3))
        .WillOnce(Return(s4))
        .WillOnce(Return(s5))
        .WillOnce(Return(s6));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("자동차 부품 조합 테스트 결과 : FAIL"));
    EXPECT_THAT(out, HasSubstr("SUV에는 TOYOTA엔진 사용 불가"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, FullFlow_TestFail_TruckWIAEngine_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    static char s1[] = "3"; //Truck
    static char s2[] = "3"; //Toyota
    static char s3[] = "1";
    static char s4[] = "1";
    static char s5[] = "2";
    static char s6[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s1))
        .WillOnce(Return(s2))
        .WillOnce(Return(s3))
        .WillOnce(Return(s4))
        .WillOnce(Return(s5))
        .WillOnce(Return(s6));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("자동차 부품 조합 테스트 결과 : FAIL"));
    EXPECT_THAT(out, HasSubstr("Truck에는 WIA엔진 사용 불가"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, FullFlow_TestFail_TruckMandoBrake_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    static char s1[] = "3"; //Truck
    static char s2[] = "1"; //Toyota
    static char s3[] = "1"; //Mando
    static char s4[] = "1";
    static char s5[] = "2";
    static char s6[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s1))
        .WillOnce(Return(s2))
        .WillOnce(Return(s3))
        .WillOnce(Return(s4))
        .WillOnce(Return(s5))
        .WillOnce(Return(s6));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("자동차 부품 조합 테스트 결과 : FAIL"));
    EXPECT_THAT(out, HasSubstr("Truck에는 Mando제동장치 사용 불가"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, FullFlow_TestFail_BoschBrakeNotBoshSteering_ThenExit) {
    MockCarAssembleApp app;
    InSequence seq;

    static char s1[] = "1";
    static char s2[] = "1";
    static char s3[] = "3"; //bosh brake
    static char s4[] = "2"; //not bosch (mobis) steering
    static char s5[] = "2";
    static char s6[] = "exit";

    EXPECT_CALL(app, GetInput())
        .WillOnce(Return(s1))
        .WillOnce(Return(s2))
        .WillOnce(Return(s3))
        .WillOnce(Return(s4))
        .WillOnce(Return(s5))
        .WillOnce(Return(s6));

    ::testing::internal::CaptureStdout();
    EXPECT_THROW(app.Run(), ExitCalled);
    std::string out = ::testing::internal::GetCapturedStdout();

    EXPECT_THAT(out, HasSubstr("자동차 부품 조합 테스트 결과 : FAIL"));
    EXPECT_THAT(out, HasSubstr("Bosch제동장치에는 Bosch조향장치 이외 사용 불가"));
    EXPECT_THAT(out, HasSubstr("바이바이"));
}

TEST_F(CarAssembleAppTestFixture, TC1) {
    MockCarAssembleApp app;
    EXPECT_TRUE(app.IsStartPage(eCarTypePage));
}
