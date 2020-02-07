#pragma once

class Object
{
    public:
        Object(const std::string & type);

        std::string GetType();

    private:
        std::string type;

};
