#pragma once
#include "i_exception.hpp"

#include <cstdlib>
#include <cstring>
#include <string>

#include "exception_type.hpp"
#include "string_helper.hpp"

using namespace std;

namespace vcc
{
    class BaseException : public IException
    {
        private:
            ExceptionType _Type = ExceptionType::NA;
            wstring _Message = L"";
        protected:
            BaseException() : BaseException(ExceptionType::NA) {}
            BaseException(ExceptionType type) : BaseException(type, L"") {}
            BaseException(ExceptionType type, wstring message)
            {
                this->_Type = type;
                this->_Message = message;
            }
            ~BaseException() {}
        
        public:
            virtual ExceptionType GetErrorType() override { return this->_Type; }
            virtual int64_t GetErrorCode() override { return static_cast<int64_t>(this->_Type); }
            virtual wstring GetErrorMessage() override { return this->_Message; }
            virtual void SetErrorMessage(wstring message) override { this->_Message = message; }

            virtual const char* what() const throw () override
            {
                // Note: Should use Message instead of what as Error Message must be wstring
                // for catch exception by message
                size_t len = this->_Message.length();
                char *str = new char[len + 1];
                memset(str, 0, len + 1);
                wcstombs(str, this->_Message.c_str(), len);
                return str;
            }

    };
}
