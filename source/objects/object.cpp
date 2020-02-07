#include "common/runtime.h"
#include "objects/object.h"

Object::Object(const std::string & type)
{
    this->type = type;
}

std::string Object::GetType()
{
    return this->type;
}
