/*
** logger.h
** @brief   : Logs shit when enabled
*/

class Logger
{
    public:
        static void Initialize(bool enable);

        static void Exit();

        static bool IsEnabled();

        static FILE * GetFile();

    private:
        static inline FILE * file = nullptr;
        static inline bool enabled = false;
};

/*
** {Function Name}:{Line}
** {Resolved printf stuff}
** {Newline}
** {Newline}
*/

#define LOG(format, ...) \
    if (Logger::IsEnabled()) \
        fprintf(Logger::GetFile(), "%s:%d:\n" format "\n\n", __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__); \
        fflush(Logger::GetFile());
