#pragma once
#include <exception>

namespace vcc
{
    class IException : public std::exception
    {
        protected:
            IException() {}
            ~IException() {}
    };
}
