#pragma once

class DataModule : public Module
{
    public:
        enum EncodeFormat
        {
            BASE64,
            HEX
        };

        enum ContainerType
        {
            DATA,
            STRING
        };

        DataModule();
        virtual ~DataModule();

        ModuleType GetModuleType() const { return M_DATA; }
};
