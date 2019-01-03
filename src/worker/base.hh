#pragma once

#include <string>

namespace fiio{
    class base{
        public:
            enum image_type{
                jpeg,
                png
            };
            base(image_type f):
                _format(f)
            {}

            inline image_type format() { return _format; }
            virtual void save(const std::string &filename) = 0;

        private:
            image_type _format;
    };
}
