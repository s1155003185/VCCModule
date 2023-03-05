#include "git_service.hpp"

#include <regex>

#include "git_constant.hpp"
#include "log_property.hpp"
#include "process_service.hpp"
#include "string_helper.hpp"

namespace vcc
{
    wstring GitService::Execute(string command)
    {
        LogProperty defaultLogProperty;
        return GitService::Execute(defaultLogProperty, L"", command);
    }
    
    wstring GitService::Execute(LogProperty &logProperty, wstring userId, string command)
    {
        return ProcessService::Execute(logProperty, GIT_LOG_ID, userId, GIT_PROCESS_ID, command);
    }

    wstring GitService::GetVersion()
    {
        LogProperty defaultLogProperty;
        return GitService::GetVersion(defaultLogProperty, L"");
    }
    
    wstring GitService::GetVersion(LogProperty &logProperty, wstring userId)
    {
        string cmd = "git --version";
        wstring cmdResult = ProcessService::Execute(logProperty, GIT_LOG_ID, userId, GIT_PROCESS_ID, cmd);
        
        wsmatch m;
        if (regex_search(cmdResult, m, wregex(L"[0-9]+.[0-9]+.[0-9]+")))
            return m[0];
        return L"";
    }

    void GitService::InitializeWorkspace(string workspace)
    {
        LogProperty defaultLogProperty;
        GitService::InitializeWorkspace(defaultLogProperty, L"", workspace);
    }

    void GitService::InitializeWorkspace(LogProperty &logProperty, wstring userId, string workspace)
    {
        string cmd = "git init";
        if (!workspace.empty())
            cmd += " " + workspace;
        ProcessService::Execute(logProperty, GIT_LOG_ID, userId, GIT_PROCESS_ID, cmd);
    }
}