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
        base(fiio::image_format format, std::string fname);

        virtual void save(std::string fname) = 0;
        virtual void load(std::string fname) = 0;

        inline fiio::image_format format() { return _format; }
        inline std::string filename() { return _filename; }

    private:
        fiio::image_format _format;
        std::string _filename = "";
    };
}
