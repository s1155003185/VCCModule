#pragma once

#include <assert.h>
#include <string>

#include "base_property.hpp"
#include "class_macro.hpp"

namespace vcc
{
    enum class LogPropertyType
    {
        None,
        All
    };

    class LogProperty : public BaseProperty<LogProperty>
    {
        // General
        GETSET(std::wstring, UserID, L"");
        
        GETSET(bool, IsConsoleLog, false);
        GETSET(std::wstring, FilePath, L"");
        // Debug
        GETSET(bool, IsLogDebug, false);
        // Thread
        GETSET(bool, IsLogThread, false);
        // Terminal
        GETSET(bool, IsLogTerminal, false);
        GETSET(bool, IsLogTerminalResult, false);
        // Process
        GETSET(bool, IsLogProcess, false);
        GETSET(bool, IsLogProcessResult, false);
        // SQL
        GETSET(bool, IsLogSQL, false);
        GETSET(bool, IsLogSQLResult, false);
    public:
        LogProperty() {}
        LogProperty(LogPropertyType logPropertyType, std::wstring filePath = L"") {
            Init(logPropertyType, filePath);
        }
        virtual ~LogProperty() {}

        void Init(LogPropertyType logPropertyType, std::wstring filePath = L"") const {
            switch (logPropertyType)
            {
            case LogPropertyType::None:
                this->SetIsConsoleLog(false);
                this->SetFilePath(L"");

                this->SetIsLogDebug(false);

                this->SetIsLogThread(false);

                this->SetIsLogTerminal(false);
                this->SetIsLogTerminalResult(false);

                this->SetIsLogProcess(false);
                this->SetIsLogProcessResult(false);

                this->SetIsLogSQL(false);
                this->SetIsLogSQLResult(false);
                break;
            case LogPropertyType::All:
                this->SetIsConsoleLog(true);
                this->SetFilePath(filePath);
                assert(!filePath.empty());

                this->SetIsLogDebug(true);
                
                this->SetIsLogThread(true);

                this->SetIsLogTerminal(true);
                this->SetIsLogTerminalResult(true);

                this->SetIsLogProcess(true);
                this->SetIsLogProcessResult(true);

                this->SetIsLogSQL(true);
                this->SetIsLogSQLResult(true);
                break;            
            default:
                assert(false);
                break;
            }
        }
    };
}
