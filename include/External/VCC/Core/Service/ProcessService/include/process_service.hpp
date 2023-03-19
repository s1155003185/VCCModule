#pragma once
#include "base_service.hpp"

#include <string>

#include "log_property.hpp"

namespace vcc
{
    class ProcessService : public BaseService
    {
        public:
            ProcessService() : BaseService() {}
            ~ProcessService() {}

            static std::wstring Execute(std::string process, std::string command);
            static std::wstring Execute(LogProperty &logProperty, std::wstring id, std::wstring userId, std::string process, std::string command);
    };
}