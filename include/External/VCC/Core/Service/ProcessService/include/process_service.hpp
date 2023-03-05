#pragma once
#include "base_service.hpp"

#include <string>

#include "log_property.hpp"

using namespace std;

namespace vcc
{
    class ProcessService : public BaseService
    {
        public:
            ProcessService() : BaseService() {}
            ~ProcessService() {}

            static wstring Execute(string process, string command);
            static wstring Execute(LogProperty &logProperty, wstring id, wstring userId, string process, string command);
    };
}