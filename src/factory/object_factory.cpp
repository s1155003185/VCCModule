#include "object_factory.hpp"

#include <assert.h>
#include <memory>

#include "exception_macro.hpp"
#include "i_object.hpp"
#include "object_type.hpp"

std::shared_ptr<vcc::IObject> ObjectFactory::create(const ObjectType &objectType, std::shared_ptr<vcc::IObject> parentObject)
{
    std::shared_ptr<vcc::IObject> result = nullptr;
    TRY
        switch (objectType)
        {
        default:
            assert(false);
            break;
        }
        if (result != nullptr)
            result->setParentObject(parentObject);
    CATCH
    return result;
}
