#pragma once

using namespace std;

namespace vcc
{
    class IObject
    {
        protected:
            IObject() {}
            ~IObject() {}
        public:
            virtual shared_ptr<IObject> Clone() = 0;
    };
}
