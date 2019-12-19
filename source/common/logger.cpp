#include "common/runtime.h"

void Logger::Initialize(bool enable)
{
    if (!enabled)
        return;

    file = freopen("love.log", "w", stderr);
    enabled = enable;
}

bool Logger::IsEnabled()
{
    return enabled;
}

FILE * Logger::GetFile()
{
    return file;
}

void Logger::Exit()
{
    if (!IsEnabled())
        return;

    fclose(file);
}
