#pragma once

#include "common/type.h"
#include "objects/object.h"

struct Proxy
{
	// Holds type information (see types.h).
	love::Type * type;

	// Pointer to the actual object.
	Object * object;
};
