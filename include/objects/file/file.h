#pragma once

#include "objects/filedata/filedata.h"

class File : public Object
{
    public:
        static love::Type type;

        enum Mode
        {
            CLOSED,
            READ,
            WRITE,
            APPEND
        };

        static const int64_t ALL = -1;

        File(const std::string & filename);
        ~File();

        FileData * Read(int64_t size = ALL);

        int64_t Read(void * destination, int64_t size);

        bool Write(Data * data, int64_t size);
        bool Write(const void * data, int64_t size);

        const char * GetMode();

        bool Open(File::Mode mode);

        bool IsOpen();

        int64_t Tell();

        void Flush();

        void Close();

        long GetSize();

        static bool GetConstant(const char * in, Mode & out);
        static bool GetConstant(Mode in, char * out);

    private:
        std::string filename;
        Mode mode;

        FILE * fileHandle;
        bool open;

        const std::string & GetFilename() const;

        static inline std::map<char, File::Mode> m_modes =
        {
            { 'c', Mode::CLOSED },
            { 'r', Mode::READ   },
            { 'w', Mode::WRITE, },
            { 'a', Mode::APPEND }
        };
};
