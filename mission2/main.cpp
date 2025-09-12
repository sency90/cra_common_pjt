#include "CarAssembleApp.h"

#ifdef _DEBUG
#include "gmock/gmock.h"

int main() {
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else
int main() {
    CarAssembleApp app;
    app.Run();

    return 0;
}
#endif