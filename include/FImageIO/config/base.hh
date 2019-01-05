#pragma once

#include <string>

namespace fiio{
    enum class image_format{
        jpeg,
        png
    };
}

namespace fiio::config{
    class base{
    public:
        explicit base(fiio::image_format format);
        virtual void save(std::string fname) = 0;
        virtual void load(std::string fname) = 0;
    private:
        fiio::image_format _format;
    };
}
