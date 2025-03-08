
#ifndef GTEST_EXTENSION_HPP
#define GTEST_EXTENSION_HPP

#include <filesystem>
#include <gmock/gmock.h>

class GTestExtension : public ::testing::Test {
protected:
    static inline std::filesystem::path testExecutablePath;
    static inline std::filesystem::path testExecutableDirPath;
    static inline std::filesystem::path testOutputDirPath;
    static inline std::string           testSuiteName;
    std::string                         testFullName;

public:
    static int  Dummy();
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void        SetUp() override;
    void        TearDown() override;

    static void        initTestSuiteName();
    static void        initTestSuitePaths();
    void               initTestFullName();
    static std::string prepareCommandWithArguments(const std::filesystem::path &executable, const std::vector<std::string> &args);
};

#endif  // GTEST_EXTENSION_HPP
