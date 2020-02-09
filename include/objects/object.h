#pragma once

class Object
{
    public:
        Object(const std::string & type);

        std::string ToString();

    private:
        std::string type;

};
