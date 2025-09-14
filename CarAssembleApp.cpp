#include "CarAssembleApp.h"

CarAssembleApp::CarAssembleApp() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void CarAssembleApp::PrintChoiceCarTypePage() {
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void CarAssembleApp::PrintChoiceEngineTypePage() {
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void CarAssembleApp::PrintChoiceBrakeTypePage() {
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void CarAssembleApp::PrintChoiceSteeringTypePage() {
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void CarAssembleApp::PrintChoiceRunAndTestPage() {
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void CarAssembleApp::PrintChoicePage(int page) {
    printf(CLEAR_SCREEN);

    if(page == eCarTypePage) {
        PrintChoiceCarTypePage();
    }
    else if(page == eEnginePage) {
        PrintChoiceEngineTypePage();
    }
    else if(page == eBrakePage) {
        PrintChoiceBrakeTypePage();
    }
    else if(page == eSteeringPage) {
        PrintChoiceSteeringTypePage();
    }
    else if(page == eRunOrTestPage) {
        PrintChoiceRunAndTestPage();
    }

    printf("===============================\n");
}

bool CarAssembleApp::WhenTypedExit(char *input) {
    return strcmp(input, "exit")==0;
}

void CarAssembleApp::ExitProgram() {
    printf("바이바이\n");
    exit(0);
}

char *CarAssembleApp::GetInput() {
    static char input[128];

    printf("INPUT > ");
    fgets(input, sizeof(input), stdin);
    return input;
}

void CarAssembleApp::RemoveEndNewLine(char *input) {
    // 엔터 개행문자 제거
    char *context = nullptr;
    strtok_s(input, "\r", &context);
    strtok_s(input, "\n", &context);
}

void CarAssembleApp::ValidateInput(const char *input, int page) {
    // 숫자로 된 대답인지 확인
    char *checkNumber;
    int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if(*checkNumber != '\0') {
        throw std::invalid_argument("숫자만 입력 가능");
    }

    if(page == eCarTypePage && !(answer >= 1 && answer <= 3)) {
        throw std::invalid_argument("차량 타입은 1 ~ 3 범위만 선택 가능");
    }

    if(page == eEnginePage && !(answer >= 0 && answer <= 4)) {
        throw std::invalid_argument("엔진은 1 ~ 4 범위만 선택 가능");
    }

    if(page == eBrakePage && !(answer >= 0 && answer <= 3)) {
        throw std::invalid_argument("제동장치는 1 ~ 3 범위만 선택 가능");
    }

    if(page == eSteeringPage && !(answer >= 0 && answer <= 2)) {
        throw std::invalid_argument("조향장치는 1 ~ 2 범위만 선택 가능");
    }

    if(page == eRunOrTestPage && !(answer >= 0 && answer <= 2)) {
        throw std::invalid_argument("Run 또는 Test 중 하나를 선택 필요");
    }
}

//ValidateInput()다음에 ChangeInputTypeToInt()가 실행되어야 한다.
int CarAssembleApp::ChangeInputTypeToInt(char *input) noexcept {
    char *checkNumber;
    int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환
    return answer;
}

bool CarAssembleApp::IsStartPage(int page) {
    return page == eCarTypePage;
}

bool CarAssembleApp::IsEndPage(int page) {
    return page == eRunOrTestPage;
}

bool CarAssembleApp::IsSelectGoBackToStartPage(int answer, int page) {
    return answer==0 && IsEndPage(page);
}

bool CarAssembleApp::IsSelectGoBackToPrevPage(int answer, int page) {
    return answer==0 && false==IsStartPage(page) && false==IsEndPage(page);
}

void CarAssembleApp::SelectParts(int answer, int page) {
    switch(page) {
    case eCarTypePage: {
        SelectCarType(answer);
        Delay(800);
        break;
    }
    case eEnginePage: {
        SelectEngine(answer);
        Delay(800);
        break;
    }
    case eBrakePage: {
        SelectBrake(answer);
        Delay(800);
        break;
    }
    case eSteeringPage: {
        SelectSteering(answer);
        Delay(800);
        break;
    }
    case eRunOrTestPage: {
        if(answer == 1) {
            RunProducedCar();
        }
        else if(answer == 2) {
            printf("Test...\n");
            Delay(1500);
            TestProducedCar();
        }
        Delay(2000);
        break;
    }
    } //switch
}

int CarAssembleApp::GetStartPage() {
    return eCarTypePage;
}

void CarAssembleApp::SelectNextPage(int answer, int &page) {
    // 처음으로 돌아가기
    if(IsSelectGoBackToStartPage(answer, page)) {
        page = GetStartPage();
        return;
    }

    // 이전으로 돌아가기
    if(IsSelectGoBackToPrevPage(answer, page)) {
        page--;
        return;
    }

    if(false == IsEndPage(page)) {
        page++;
    }
}

int CarAssembleApp::Run() {
    int current_page = GetStartPage();

    while(1) {
        PrintChoicePage(current_page);

        char *input = GetInput();
        RemoveEndNewLine(input);

        if(WhenTypedExit(input)) {
            ExitProgram();
        }

        try {
            ValidateInput(input, current_page);
        }
        catch(std::exception &ex) {
            printf("ERROR :: %s\n", ex.what());
            Delay(800);
            continue;
        }

        int answer = ChangeInputTypeToInt(input);
        SelectParts(answer, current_page);
        SelectNextPage(answer, current_page);
    }

    return 0;
}

void CarAssembleApp::SelectCarType(int answer) {
    car_type = CarTypeFactory::Create(answer);
    printf("차량 타입으로 %s을 선택하셨습니다.\n", car_type->GetName().c_str());
}

void CarAssembleApp::SelectEngine(int answer) {
    engine_type = EngineTypeFactory::Create(answer);
    printf("%s 엔진을 선택하셨습니다.\n", engine_type->GetName().c_str());
}

void CarAssembleApp::SelectBrake(int answer) {
    brake_type = BrakeTypeFactory::Create(answer);
    printf("%s 제동장치를 선택하셨습니다.\n", brake_type->GetName().c_str());
}

void CarAssembleApp::SelectSteering(int answer) {
    steering_type = SteeringTypeFactory::Create(answer);
    printf("%s 조향장치를 선택하셨습니다.\n", steering_type->GetName().c_str());
}

int CarAssembleApp::IsValidCheck() {
    CommonFunction &cf = CommonFunction::GetInstance();
    if(cf.EqualsIgnoreCase(car_type->GetName(),"Sedan") && cf.EqualsIgnoreCase(brake_type->GetName(),"CONTINENTAL")) {
        return false;
    }
    else if(cf.EqualsIgnoreCase(car_type->GetName(), "SUV") && cf.EqualsIgnoreCase(engine_type->GetName(), "TOYOTA")) {
        return false;
    }
    else if(cf.EqualsIgnoreCase(car_type->GetName(), "Truck") && cf.EqualsIgnoreCase(engine_type->GetName(), "WIA")) {
        return false;
    }
    else if(cf.EqualsIgnoreCase(car_type->GetName(), "Truck") && cf.EqualsIgnoreCase(brake_type->GetName(), "MANDO")) {
        return false;
    }
    else if(cf.EqualsIgnoreCase(brake_type->GetName(), "BOSCH") && false==cf.EqualsIgnoreCase(steering_type->GetName(), "BOSCH")) {
        return false;
    }

    return true;
}

void CarAssembleApp::PrintAssembledCarType() {
    printf("Car Type : %s\n", car_type->GetName().c_str());
}

void CarAssembleApp::PrintAssembledCarEngineType() {
    printf("Engine : %s\n", engine_type->GetName().c_str());
}

void CarAssembleApp::PrintAssembeldCarBrakeType() {
    printf("Brake System : %s\n", brake_type->GetName().c_str());
}

void CarAssembleApp::PrintAssembledCarSteeringType() {
    printf("SteeringSystem : %s\n", steering_type->GetName().c_str());
}

void CarAssembleApp::RunProducedCar() {
    if(IsValidCheck() == false) {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if(engine_type->GetName() == "BROKEN") {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    PrintAssembledCarType();
    PrintAssembledCarEngineType();
    PrintAssembeldCarBrakeType();
    PrintAssembledCarSteeringType();

    printf("자동차가 동작됩니다.\n");
}

void CarAssembleApp::TestProducedCar() {
    CommonFunction &cf = CommonFunction::GetInstance();
    if(cf.EqualsIgnoreCase(car_type->GetName(), "Sedan") && cf.EqualsIgnoreCase(brake_type->GetName(), "CONTINENTAL")) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if(cf.EqualsIgnoreCase(car_type->GetName(), "SUV") && cf.EqualsIgnoreCase(engine_type->GetName(), "TOYOTA")) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if(cf.EqualsIgnoreCase(car_type->GetName(), "Truck") && cf.EqualsIgnoreCase(engine_type->GetName(), "WIA")) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if(cf.EqualsIgnoreCase(car_type->GetName(), "Truck") && cf.EqualsIgnoreCase(brake_type->GetName(), "MANDO")) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if(cf.EqualsIgnoreCase(brake_type->GetName(), "BOSCH") && false == cf.EqualsIgnoreCase(steering_type->GetName(), "BOSCH")) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}
