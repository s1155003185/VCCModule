#pragma once

#include "base_property.hpp"
#include "class_macro.hpp"

#include "file_constant.hpp"
#include "log_type.hpp"

namespace vcc
{
    class LogProperty : public BaseProperty
    {
        GETSET(bool, IsConsoleLog, true);
        GETSET(PATH, FilePath, "");
    public:
        LogProperty() {}
        ~LogProperty() {}
    };
}
