#include <gtest/gtest.h>

#include "command_service.hpp"
#include "log_property.hpp"
#include "string_helper.hpp"

using namespace std;
using namespace vcc;

TEST(CommandTest, CommandTest)
{
    LogProperty logProperty;
    logProperty.SetIsConsoleLog(false);
    logProperty.SetIsLogCommand(false);
    logProperty.SetIsLogCommandResult(false);
    EXPECT_TRUE(HasPrefix(CommandService::Execute(logProperty, "git --version"), L"git version"));
}
