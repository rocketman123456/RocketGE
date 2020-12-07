#pragma once
#include "GECore/Core.h"

namespace Rocket {
    enum class ObjectType
    {
        None = 0,
        Runtime,
        Static,
    };

#define OBJECT_CLASS_TYPE(category, type) static category GetStaticType() { return category::type; }\
        virtual category GetObjectType() const override { return GetStaticType(); }\
        virtual const char* GetName() const override { return #type; }

    Interface IObject
    {
    public:
        virtual ObjectType GetObjectType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
    };
}