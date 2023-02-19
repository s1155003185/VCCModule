#pragma once
#include <exception>
#include <string>

#include "exception_type.hpp"

using namespace std;

namespace vcc
{
    class IException : public std::exception
    {
        protected:
            IException() {}
            ~IException() {}
        public:
            virtual ExceptionType GetErrorType() = 0;
            virtual int64_t GetErrorCode() = 0;
            virtual wstring GetErrorMessage() = 0;
            virtual void SetErrorMessage(wstring message) = 0;
    };
}
