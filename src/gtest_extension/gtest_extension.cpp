
#include "gtest_extension.hpp"

#include <numeric>

#if defined __linux__
# include <limits.h>  // NOLINT
#elif defined __APPLE__
# include <mach-o/dyld.h>
#elif defined _WIN32
# include <windows.h>
#endif  // OS

int GTestExtension::Dummy() {
    constexpr int result = 42;
    return result;
}

void GTestExtension::SetUpTestSuite() {
    initTestSuiteName();

    ASSERT_NO_FATAL_FAILURE(initTestSuitePaths());

    if (!fs::exists(testOutputDirPath)) {
        fs::create_directories(testOutputDirPath);
    }
}

void GTestExtension::TearDownTestSuite() {
}

void GTestExtension::SetUp() {
    ASSERT_NO_FATAL_FAILURE(initTestFullName());
}

void GTestExtension::TearDown() {
}

void GTestExtension::initTestSuiteName() {
    testSuiteName = ::testing::UnitTest::GetInstance()->current_test_suite()->name();
}

void GTestExtension::initTestSuitePaths() {
#if defined __linux__
    std::array<char, PATH_MAX> pathBuffer{};
    ssize_t                    count;

    count = readlink("/proc/self/exe", pathBuffer.data(), PATH_MAX);
    ASSERT_NE(count, -1);
    ASSERT_NE(count, PATH_MAX);

    pathBuffer[count]  = '\0';
    testExecutablePath = fs::path{pathBuffer.data()};
#elif defined __APPLE__
    char    *pathBuffer    = nullptr;
    uint32_t pathBufferLen = 0;
    int      retVal;

    retVal = _NSGetExecutablePath(pathBuffer, &pathBufferLen);
    ASSERT_EQ(retVal, -1);
    pathBuffer = static_cast<decltype(pathBuffer)>(malloc(pathBufferLen));
    ASSERT_NE(pathBuffer, nullptr);

    retVal = _NSGetExecutablePath(pathBuffer, &pathBufferLen);
    ASSERT_EQ(retVal, 0);

    testExecutablePath = fs::path{pathBuffer};
    free(pathBuffer);
#elif defined _WIN32
    char   *value;
    errno_t result;

    result = _get_pgmptr(&value);
    ASSERT_EQ(result, 0);

    testExecutablePath = fs::path{value};
#endif  // OS
    testExecutableDirPath = testExecutablePath.parent_path();
    testOutputDirPath     = testExecutableDirPath / "tests_output";
}

void GTestExtension::initTestFullName() {
    const ::testing::TestInfo *testInfo;

    testInfo = UnitTest::GetInstance()->current_test_info();
    ASSERT_NE(testInfo, nullptr) << "Can't retrieve test info\n";

    testFullName += testInfo->test_suite_name();
    testFullName += ".";
    testFullName += testInfo->name();
}

std::string GTestExtension::prepareCommandWithArguments(const fs::path &executable, const std::vector<std::string> &args) {
    std::string result;

    if (args.empty()) {
        return executable;
    }

    result += std::string{executable};
    for (const auto &arg : args) {
        result += " ";
        result += arg;
    }

    return result;
}
