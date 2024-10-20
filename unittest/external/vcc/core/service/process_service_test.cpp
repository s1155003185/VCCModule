#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "process_service.hpp"
#include "log_config.hpp"
#include "string_helper.hpp"

using namespace vcc;

TEST(ProcessServiceTest, Normal)
{
    EXPECT_TRUE(ProcessService::Execute(nullptr, L"", L"git --version").starts_with(L"git version"));
}

TEST(ProcessServiceTest, NormalWithWorkspace)
{
    EXPECT_TRUE(ProcessService::Execute(nullptr, L"", L"..", L"git --version").starts_with(L"git version"));
}

TEST(ProcessServiceTest, ParseCMDToken)
{
    std::vector<std::string> tokens = ProcessService::ParseCMDLinux("");
    std::vector<std::string> expectedTokens;
    EXPECT_EQ(tokens, expectedTokens);

    tokens = ProcessService::ParseCMDLinux("a");
    expectedTokens.clear();
    expectedTokens.push_back("a");
    EXPECT_EQ(tokens, expectedTokens);

    tokens = ProcessService::ParseCMDLinux("a b");
    expectedTokens.clear();
    expectedTokens.push_back("a");
    expectedTokens.push_back("b");
    EXPECT_EQ(tokens, expectedTokens);

    tokens = ProcessService::ParseCMDLinux("a \"a b c\"");
    expectedTokens.clear();
    expectedTokens.push_back("a");
    expectedTokens.push_back("a b c");
    EXPECT_EQ(tokens, expectedTokens);

    tokens = ProcessService::ParseCMDLinux("a \"a \\\"b\\\" c\"");
    expectedTokens.clear();
    expectedTokens.push_back("a");
    expectedTokens.push_back("a \"b\" c");
    EXPECT_EQ(tokens, expectedTokens);

    tokens = ProcessService::ParseCMDLinux("a 'a \\\'b\\\' c'");
    expectedTokens.clear();
    expectedTokens.push_back("a");
    expectedTokens.push_back("a 'b' c");
    EXPECT_EQ(tokens, expectedTokens);
}

TEST(ProcessServiceTest, Exception)
{
    bool isError = false;
    try {
        ProcessService::Execute(nullptr, L"", L"git -version");
    } catch (std::exception &e) {
        std::string exceptStr(e.what());
        EXPECT_TRUE(exceptStr.find("unknown option") != std::string::npos);
        isError = true;
    }
    EXPECT_TRUE(isError);
}
