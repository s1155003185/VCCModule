#include "command_service.hpp"

#include "exception_macro.hpp"
#include "exception_type.hpp"
#include "log_property.hpp"
#include "log_service.hpp"
#include "string_helper.hpp"

namespace vcc
{
    std::wstring CommandService::Execute(std::string cmd)
    {
        LogProperty defaultLogProperty;
        return CommandService::Execute(defaultLogProperty, L"", L"", cmd);
    }

    std::wstring CommandService::Execute(LogProperty &logProperty, std::wstring id, std::wstring userId, std::string cmd)
    {
        LogService::LogCommand(logProperty, id, userId, str2wstr(cmd));

        char buffer[1024];
        FILE* p = popen(cmd.c_str(), "r");
        if (p == nullptr)
            THROW_EXCEPTION(ExceptionType::CUSTOM_ERROR, L"Cannot Execute Command: " + str2wstr(cmd));
    
        std::wstring result;
        try {
            while (!feof(p)) {
                if (fgets(buffer, sizeof(buffer), p) != nullptr)
                    result += str2wstr(buffer);
            }
        } catch (exception &e) {
            pclose(p);
            THROW_EXCEPTION(ExceptionType::CUSTOM_ERROR, str2wstr(e.what()));
        }
        int status = pclose(p);
        if (WEXITSTATUS(status) != 0)
            THROW_EXCEPTION(ExceptionType::CUSTOM_ERROR, result);
        LogService::LogCommandResult(logProperty, id, userId, result);
        return result;
    }
}