#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
#include <thread>

#include "CarType.h"
#include "CarTypeFactory.h"
#include "EngineType.h"
#include "EngineTypeFactory.h"
#include "BrakeType.h"
#include "BrakeTypeFactory.h"
#include "SteeringType.h"
#include "SteeringTypeFactory.h"
#include "CommonFunction.h"
#include "PrintManager.h"
#include "PageEnum.h"

class CarAssembleApp {
public:
    ICarType *car_type;
    IEngineType *engine_type;
    IBrakeType *brake_type;
    ISteeringType *steering_type;

    PrintManager &pm;

    CarAssembleApp();

    int Run();

public:
    void Delay(int ms);

    bool WhenTypedExit(char *input);
    virtual void ExitProgram();

    virtual char *GetInput();
    void RemoveEndNewLine(char *input);
    void ValidateInput(const char *input, PageEnum page);

    //ValidateInput()다음에 ChangeInputTypeToInt()가 실행되어야 한다.
    int ChangeInputTypeToInt(char *input) noexcept;

    bool IsSelectGoBackToStartPage(int answer, PageEnum page);
    bool IsSelectGoBackToPrevPage(int answer, PageEnum page);
    void MovePage(int answer, PageEnum &page);

    void SelectParts(int answer, PageEnum page);

    void SelectCarType(int answer);
    void SelectEngineType(int answer);
    void SelectBrakeType(int answer);
    void SelectSteeringType(int answer);

    int IsValidCheck();

    void RunProducedCar();
    void TestProducedCar();
};
