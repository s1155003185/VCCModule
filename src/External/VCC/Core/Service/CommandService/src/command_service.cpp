#include "command_service.hpp"

#include "exception_macro.hpp"
#include "exception_type.hpp"
#include "log_property.hpp"
#include "log_service.hpp"
#include "string_helper.hpp"

namespace vcc
{
    wstring CommandService::Execute(string cmd)
    {
        LogProperty defaultLogProperty;
        return CommandService::Execute(defaultLogProperty, cmd);
    }

    wstring CommandService::Execute(LogProperty &logProperty, string cmd)
    {
        LogService::LogCommand(logProperty, str2wstr(cmd));

        char buffer[1024];
        FILE* p = popen(cmd.c_str(), "r");
        if (p == nullptr)
            THROW_EXCEPTION(ExceptionType::CUSSTOM_ERROR, L"Cannot Execute Command: " + str2wstr(cmd));
    
        wstring result;
        try {
            while (!feof(p)) {
                if (fgets(buffer, sizeof(buffer), p) != nullptr)
                    result += str2wstr(buffer);
            }
        } catch (...) {
            pclose(p);
            throw;
        }
        int status = pclose(p);
        if (WEXITSTATUS(status) != 0)
            THROW_EXCEPTION(ExceptionType::CUSSTOM_ERROR, result);
        LogService::LogCommandResult(logProperty, result);
        return result;
    }
}