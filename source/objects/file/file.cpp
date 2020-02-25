#include "common/runtime.h"
#include <sys/stat.h>

#include "objects/file/file.h"

love::Type File::type("File", &Object::type);

File::File(const std::string & filename)
{
    this->filename = filename;
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
    switch (this->mode)
    {
        case Mode::APPEND:
            return "a";
        case Mode::CLOSED:
            return "c";
        case Mode::READ:
            return "r";
        default:
            return "w";
    }
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

    this->fileHandle = fopen(this->GetFilename().c_str(), openMode);

    if (!this->fileHandle)
        return false;

    this->mode = mode;
    this->open = true;

    return true;
}

bool File::Write(const void * data, int64_t size)
{
    if (!this->fileHandle || (this->mode != WRITE && this->mode != APPEND))
        throw love::Exception("File is not opened for writing");

    if (!this->open && !this->Open(Mode::WRITE))
        throw love::Exception("Could not write to file %s", this->GetFilename().c_str());

    int64_t written = fwrite(data, 1, size, this->fileHandle);

    if (written != size)
        return false;

    return true;
}

void File::Flush()
{
    fflush(this->fileHandle);
}

void File::Close()
{
    this->mode = File::Mode::CLOSED;
    fclose(this->fileHandle);
}

int64_t File::Read(void * destination, int64_t size)
{
    if (!this->open && !this->Open(READ))
        throw love::Exception("File is not opened for reading.");

    long selfSize = this->GetSize();

    size = (size == ALL) ? selfSize : size;
    size = (size > selfSize) ? selfSize : size;

    if (size < 0)
        throw love::Exception("Invalid read size.");

    fread(destination, 1, size, this->fileHandle);
    // destination[size] = '\0';

    return size;
}

int64_t File::Tell()
{
    if (!this->fileHandle)
        return -1;

    return ftell(this->fileHandle);
}

FileData * File::Read(int64_t size)
{
    if (!this->open && !this->Open(READ))
        throw love::Exception("Could not read file %s.", this->GetFilename().c_str());

    int64_t max = this->GetSize();
    int64_t current = this->Tell();

    size = (size == ALL) ? max : size;

    if (size < 0)
        throw love::Exception("Invalid read size.");

    if (current < 0)
        current = 0;
    else if (current > max)
        current = max;

    if (current + size > max)
        size = max - current;

    FileData * fileData = new FileData(size, this->GetFilename());

    int64_t bytesRead = this->Read(fileData->GetData(), size);

    if (bytesRead < 0 || (bytesRead == 0 && bytesRead != size))
    {
        delete fileData;
        throw love::Exception("Could not read from file.");
    }

    if (bytesRead < size)
    {
        FileData * tmp = new FileData(bytesRead, this->GetFilename());
        memcpy(tmp->GetData(), fileData->GetData(), (size_t)bytesRead);
        fileData->Release();

        fileData = tmp;
    }

    if (!this->open)
        this->Close();

    return fileData;
}

bool File::Write(Data * data, int64_t size)
{
    return this->Write(data->GetData(), (size == ALL) ? data->GetSize() : size);
}

const std::string & File::GetFilename() const
{
    return this->filename;
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
