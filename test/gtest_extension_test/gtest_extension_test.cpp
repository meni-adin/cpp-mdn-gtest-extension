
#include <gmock/gmock.h>

#include "mdn/gtest_extension.hpp"

using namespace testing;

class GTestExtensionTest : public ::testing::Test {};

TEST_F(GTestExtensionTest, Dummy) {
    const int dummy = mdn::GTestExtension::Dummy();
    ASSERT_EQ(dummy, 42);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
