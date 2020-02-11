#include "common/runtime.h"
#include <sys/stat.h>

#include "objects/file/file.h"

love::Type File::type("File", &Object::type);

File::File(const char * path)
{
    this->path = strdup(path);
    this->open = false;
}

File::~File()
{
    if (this->open)
        this->Flush();

    this->Close();
}

long File::GetSize()
{
    long size = 0;

    fseek(this->fileHandle, 0, SEEK_END);
    size = ftell(this->fileHandle);
    rewind(this->fileHandle);

    return size;
}

const char * File::GetMode()
{
    return this->mode;
}

bool File::IsOpen()
{
    return this->open;
}

bool File::Open(File::Mode mode)
{
    char openMode[3] = { 0 };
    this->GetConstant(mode, openMode);
    strcat(openMode, "b");

    this->fileHandle = fopen(this->path, openMode);

    if (!this->fileHandle)
        return false;

    this->mode = strdup(openMode);
    this->open = true;

    return true;
}

void File::Write(const char * data, size_t length)
{
    if (!this->open)
        return;

    fwrite(data, 1, length, this->fileHandle);
}

void File::Flush()
{
    fflush(this->fileHandle);
}

void File::Close()
{

    fclose(this->fileHandle);
}

char * File::Read()
{
    if (!this->open)
        return NULL;

    char * buffer;

    long size = this->GetSize();

    buffer = (char *)malloc(size * sizeof(char));

    fread(buffer, 1, size, this->fileHandle);

    buffer[size] = '\0';

    return buffer;
}

bool File::GetConstant(const char * in, Mode & out)
{
    if (m_modes.find(*in) != m_modes.end())
    {
        out = m_modes[*in];
        return true;
    }

    return false;
}

bool File::GetConstant(Mode in, char * out)
{
    for (auto item = m_modes.begin(); item != m_modes.end(); item++)
    {
        if (m_modes[item->first] == in)
        {
            *out = item->first;
            return true;
        }
    }
    return false;
}
