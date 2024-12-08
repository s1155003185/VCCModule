#include "object_factory.hpp"

#include <assert.h>
#include <memory>

#include "exception_macro.hpp"
#include "i_object.hpp"
#include "object_type.hpp"

using namespace vcc;

std::shared_ptr<IObject> ObjectFactory::Create(const ObjectType &objectType, std::shared_ptr<IObject> parentObject)
{
    std::shared_ptr<IObject> result = nullptr;
    TRY
        switch (objectType)
        {
        default:
            assert(false);
            break;
        }
        if (result != nullptr)
            result->SetParentObject(parentObject);
    CATCH
    return result;
}
