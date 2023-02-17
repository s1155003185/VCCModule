#pragma once
#include "i_exception.hpp"

#include <cstdlib>
#include <string>

#include "class_macro.hpp"
#include "exception_type.hpp"

using namespace std;

namespace vcc
{
    class BaseException : public IException
    {
        GET(ExceptionType, ExceptionType, ExceptionType::NA)
        GETSET(wstring, Message, L"")
    protected:
        BaseException() : BaseException(ExceptionType::NA) {}
        BaseException(ExceptionType exceptionType) : BaseException(exceptionType, L"") {}
        BaseException(ExceptionType exceptionType, wstring message)
        {
            this->_ExceptionType = exceptionType;
            this->_Message = message;
        }
        ~BaseException() {}
    
    public:
		const char* what() const throw ()
		{
            // Note: Must use Message instead of what as Error Message must be wstring
            // Just to override the virtual method
            size_t len = this->_Message.length();
            char *str = new char[len + 1];
            memset(str, 0, len + 1);
    	    wcstombs(str, this->_Message.c_str(), len);
            return str;
        }
    };
}
