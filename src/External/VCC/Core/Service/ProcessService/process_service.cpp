#include "process_service.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <vector>
#include <unistd.h>

#include "exception_macro.hpp"
#include "exception_type.hpp"
#include "log_property.hpp"
#include "log_service.hpp"
#include "string_helper.hpp"

using namespace std;

namespace vcc
{
        wstring ProcessService::Execute(string process, string command)
        {
            LogProperty defaultProperty;
            return ProcessService::Execute(defaultProperty, str2wstr(process), L"", process, command);
        }

        wstring ProcessService::Execute(LogProperty &logProperty, wstring id, wstring userId, string process, string command)
        {
            LogService::LogProcess(logProperty, id, userId, str2wstr(command));

            wstring result = L"";
            try {
                // convert to token
                vector<char *> tokens;
                char *token = strtok((char *)command.c_str(), " ");
                while (token != nullptr) {
                    tokens.push_back(token);
                    token = strtok(nullptr, " ");
                }
                tokens.push_back(nullptr);

                // process
                int pipefd_stdout[2];
                int pipefd_stderr[2];
                int status;

                // pipe
                if (pipe(pipefd_stdout) < 0)
                    perror("pipe: ");
                if (pipe(pipefd_stderr) < 0)
                    perror("pipe: ");

                pid_t pid = fork();
                if (pid < 0) {
                    perror("fork: ");
                } else if (pid == 0) {
                    // child process
                    // duplicate writing end to stdout
                    dup2(pipefd_stdout[1], STDOUT_FILENO);
                    dup2(pipefd_stderr[1], STDERR_FILENO);
                    close(pipefd_stdout[0]);
                    close(pipefd_stdout[1]);
                    close(pipefd_stderr[0]);
                    close(pipefd_stderr[1]);
                    if (execvp(process.c_str(), tokens.data())) {
                        perror("execvp: ");
                        exit(-1);
                    }
                }
                // parent process
                // close writing end of pipe
                close(pipefd_stdout[1]);
                close(pipefd_stderr[1]);

                FILE *fStdout = fdopen(pipefd_stdout[0], "r");
                FILE *fStderr = fdopen(pipefd_stderr[0], "r");

                char ch;
                string tmpResult;
                while (!feof(fStdout)) {
                    ch = fgetc(fStdout);
                    tmpResult += ch;
                }
                result = str2wstr(tmpResult);

                string error;
                while (!feof(fStderr)) {
                    ch = fgetc(fStderr);
                    error += ch;
                }
                wait(&status);
                if (status != 0)
                    throw runtime_error(error);
            } catch (exception &e) {
                THROW_EXCEPTION(ExceptionType::CUSTOM_ERROR, str2wstr(string(e.what())));
            }
            LogService::LogProcessResult(logProperty, id, userId, result);
            return result;
        }
}