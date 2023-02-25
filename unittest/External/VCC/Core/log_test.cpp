#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "file_helper.hpp"
#include "log_service.hpp"

using namespace std;
using namespace vcc;

TEST(LogServiceTest, LogTest) 
{
    PATH filePath = std::filesystem::current_path() / "bin/Debug/AppLogs/LogServiceTest.log";
    remove(filePath);
    
    LogProperty property;
    property.SetIsConsoleLog(false);
    property.SetIsLogCommand(true);
    property.SetIsLogCommandResult(true);
    property.SetIsLogSQL(true);
    property.SetIsLogSQLResult(true);
    property.SetFilePath(filePath);
    wstring logInfoStr = LogService::LogInfo(property, L"id", L"user", L"message");
    wstring logWarningStr = LogService::LogWarning(property, L"id", L"user", L"message");
    wstring logErrorStr = LogService::LogError(property, L"id", L"user", L"message");
    wstring logCommandStr = LogService::LogCommand(property, L"id", L"user", L"message");
    wstring logCommandResultStr = LogService::LogCommandResult(property, L"id", L"user", L"message");
    wstring logSQLStr = LogService::LogSQL(property, L"id", L"user", L"message");
    wstring logSQLResultStr = LogService::LogSQLResult(property, L"id", L"user", L"message");
    EXPECT_EQ(logInfoStr, ReadFileSingleLline(filePath, 0));
    EXPECT_EQ(logWarningStr, ReadFileSingleLline(filePath, 1));
    EXPECT_EQ(logErrorStr, ReadFileSingleLline(filePath, 2));
    EXPECT_EQ(logCommandStr, ReadFileSingleLline(filePath, 3));
    EXPECT_EQ(logCommandResultStr, ReadFileSingleLline(filePath, 4));
    EXPECT_EQ(logSQLStr, ReadFileSingleLline(filePath, 5));
    EXPECT_EQ(logSQLResultStr, ReadFileSingleLline(filePath, 6));
}
