#pragma once

#include <string.h>

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

        File(const char * path);

        ~File();

        char * Read();

        void Write(const char * data, size_t length);

        const char * GetMode();

        bool Open(File::Mode mode);
        bool IsOpen();
        void Flush();
        void Close();

        long GetSize();

        static bool GetConstant(const char * in, Mode & out);
        static bool GetConstant(Mode in, char * out);

    private:
        const char * path;
        const char * mode;

        FILE * fileHandle;
        bool open;

        static inline std::map<char, File::Mode> m_modes =
        {
            { 'c', Mode::CLOSED },
            { 'r', Mode::READ   },
            { 'w', Mode::WRITE, },
            { 'a', Mode::APPEND }
        };
};
