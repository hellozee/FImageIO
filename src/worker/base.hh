#pragma once

#include <string>
#include <FImageIO/FImageIO>

namespace fiio::worker{
    class base{
        public:
            base(fiio::image_format f):
                _format(f)
            {}

            inline fiio::image_format format() { return _format; }
            virtual void save(const std::string &filename) = 0;

        private:
            fiio::image_format _format;
    };
}
