#pragma once
#include <string>

using namespace std;

namespace vcc
{
    class IObject
    {
        protected:
            IObject() {}
            ~IObject() {}

        public:
            virtual wstring GetKey() = 0;
    };
}
