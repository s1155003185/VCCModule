#pragma once
#include "base_service.hpp"

#include "log_property.hpp"

namespace vcc
{
    class GitService : public BaseService
    {
        public:
            GitService() : BaseService() {}
            ~GitService() {}

        static wstring Execute(string command);
        static wstring Execute(LogProperty &logProperty, wstring userId, string command);

        static wstring GetVersion();
        static wstring GetVersion(LogProperty &logProperty, wstring userId);

        static void InitializeWorkspace(string workspace);
        static void InitializeWorkspace(LogProperty &logProperty, wstring userId, string workspace);
    };
}
