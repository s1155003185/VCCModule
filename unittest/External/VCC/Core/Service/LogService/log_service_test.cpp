#include <gtest/gtest.h>

#include <filesystem>

#include "file_helper.hpp"
#include "log_service.hpp"

using namespace vcc;

TEST(LogServiceTest, LogTest) 
{
    PATH filePath = std::filesystem::current_path() / "bin/Debug/AppLogs/LogServiceTest.log";
    remove(filePath);
    
    LogProperty property;
    property.SetIsConsoleLog(false);
    property.SetFilePath(filePath);
    wstring logInfoStr = LogService::LogInfo(property, L"id", L"user", L"message");
    wstring logWarningStr = LogService::LogWarning(property, L"id", L"user", L"message");
    wstring logErrorStr = LogService::LogError(property, L"id", L"user", L"message");
    EXPECT_EQ(logInfoStr, ReadFileSingleLline(filePath, 0));
    EXPECT_EQ(logWarningStr, ReadFileSingleLline(filePath, 1));
    EXPECT_EQ(logErrorStr, ReadFileSingleLline(filePath, 2));
}
