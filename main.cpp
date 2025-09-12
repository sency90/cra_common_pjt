#ifdef _WIN32
#pragma execution_character_set("utf-8")
#include <windows.h>
#endif

#include "CarAssembleApp.h"

#ifdef _DEBUG
#include "gmock/gmock.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    CarAssembleApp app;
    app.Run();

    return 0;
}
#endif