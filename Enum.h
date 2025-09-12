#pragma once

enum PageEnum {
    eCarTypePage,
    eEnginePage,
    eBrakePage,
    eSteeringPage,
    eRunOrTestPage,
};

enum CarEnum {
    eSedanCar=1,
    eSUVCar,
    eTruckCar
};

enum EngineEnum {
    eGMEngine=1,
    eTOYOTAEngine,
    eWIAEngine
};

enum BrakeEnum {
    eMANDOBrake=1,
    eCONTINENTALBrake,
    eBOSCHBrake
};

enum SteeringEnum {
    eBOSCHSteering=1,
    eMOBISSteering
};
