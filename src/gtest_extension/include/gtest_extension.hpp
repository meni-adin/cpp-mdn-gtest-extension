
#ifndef GTEST_EXTENSION_HPP
#define GTEST_EXTENSION_HPP

#include <filesystem>
#include <gmock/gmock.h>

using namespace testing;
namespace fs = std::filesystem;

class GTestExtension : public ::testing::Test {
protected:
    static inline fs::path    testExecutablePath;
    static inline fs::path    testExecutableDirPath;
    static inline fs::path    testOutputDirPath;
    static inline std::string testSuiteName;
    std::string               testFullName;

public:
    static int  Dummy();
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void        SetUp() override;
    void        TearDown() override;

    static void        initTestSuiteName();
    static void        initTestSuitePaths();
    void               initTestFullName();
    static std::string prepareCommandWithArguments(const fs::path &executable, const std::vector<std::string> &args);
};

#endif  // GTEST_EXTENSION_HPP
