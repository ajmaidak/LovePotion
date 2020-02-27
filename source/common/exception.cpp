#include "common/runtime.h"

#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <exception>

using namespace love;

Exception::Exception(const char * format, ...)
{
    va_list args;

    int size_buffer = 256;
    int size_out;
    char * buffer;

    while (true)
    {
        buffer = new char[size_buffer];
        memset(buffer, 0, size_buffer);

        va_start(args, format);
        size_out = vsnprintf(buffer, size_buffer, format, args);
        va_end(args);

        if (size_out == size_buffer || size_out == -1 || size_out == size_buffer - 1)
            size_buffer *= 2;
        else if (size_out > size_buffer)
            size_buffer = size_out + 2;
        else
            break;

        delete[] buffer;
    }

    this->message = std::string(buffer);
    delete[] buffer;
}

Exception::~Exception() throw()
{}
