#pragma once
#include "base_service.hpp"

#include <string>

#include "log_property.hpp"

namespace vcc
{
    class ProcessService : public BaseService
    {
        private:
            #ifdef _WIN32
            static std::wstring _ExecuteWindow(std::wstring process, std::wstring command);
            #else
            static std::wstring _ExecuteLinux(std::string process, std::string command);
            #endif

            static std::wstring _Execute(std::wstring process, std::wstring command);

        public:
            ProcessService() : BaseService() {}
            ~ProcessService() {}

            static std::wstring Execute(std::wstring process, std::wstring command);
            static std::wstring Execute(LogProperty &logProperty, std::wstring id, std::wstring userId, std::wstring process, std::wstring command);
    };
}