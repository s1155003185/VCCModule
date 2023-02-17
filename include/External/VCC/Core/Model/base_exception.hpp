#pragma once
#include "i_exception.hpp"

namespace vcc
{
    class BaseException : public IException
    {
    protected:
        BaseException() {}
        ~BaseException() {}
    };
}
