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

        static std::wstring Execute(std::string command);
        static std::wstring Execute(LogProperty &logProperty, std::wstring userId, std::string command);

        static std::wstring GetVersion();
        static std::wstring GetVersion(LogProperty &logProperty, std::wstring userId);

        static void InitializeWorkspace(std::string workspace);
        static void InitializeWorkspace(LogProperty &logProperty, std::wstring userId, std::string workspace);
    };
}
