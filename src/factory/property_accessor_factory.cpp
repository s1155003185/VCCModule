#include "property_accessor_factory.hpp"

#include <assert.h>
#include <memory>

#include "base_property_accessor.hpp"
#include "i_object.hpp"
#include "i_property_accessor.hpp"

std::shared_ptr<vcc::IPropertyAccessor> PropertyAccessorFactory::create(std::shared_ptr<vcc::IObject> object)
{
    assert(object != nullptr);

    switch (object->getObjectType())
    {
    default:
        assert(false);
        break;
    }
    return nullptr;
}
