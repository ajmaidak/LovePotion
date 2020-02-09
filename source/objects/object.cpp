#include "common/runtime.h"
#include "objects/object.h"

Object::Object(const std::string & type)
{
    this->type = type;
    snprintf(this->type.data(), 64, "%s: %p", type.c_str(), this);
}

std::string Object::ToString()
{
    return this->type;
}
