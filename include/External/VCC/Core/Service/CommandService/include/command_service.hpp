#pragma once
#include "base_service.hpp"

#include <string>

#include "log_property.hpp"

using namespace std;

namespace vcc
{
    class CommandService : public BaseService
    {
        public:
            CommandService() : BaseService() {}
            ~CommandService() {}

            static wstring Execute(string cmd);
            static wstring Execute(LogProperty &logProperty, wstring id, wstring userId, string cmd);
    };
}