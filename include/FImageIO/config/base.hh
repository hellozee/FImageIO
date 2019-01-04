#pragma once

#include <string>

namespace fiio::config{
    class base{
    public:
        virtual void save(std::string fname) = 0;
        virtual void load(std::string fname) = 0;
    };
}
