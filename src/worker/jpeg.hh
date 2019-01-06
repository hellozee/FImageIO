#pragma once

#include "base.hh"

#include "jpeglib.h"
#include <memory>
#include <vector>

namespace fiio::worker{
    class jpeg : public fiio::worker::base{
        public:
            explicit jpeg(const std::string &filename);
            jpeg(const jpeg& rhs);

            void save(const std::string &filename);

            inline size_t width() { return _width; }
            inline size_t height() { return _height; }
            inline size_t pixel_size() { return _pixel_size; }
            inline int colorspace() { return _colorspace; }
            inline void set_quality(int value) { _quality = value; } 

        private:
            int _colorspace;
            size_t _width, _height, _pixel_size;
            std::shared_ptr<::jpeg_error_mgr> _error_manager;
            std::vector<std::vector<uint8_t>> _pixels;
            int _quality = 95;
    };
}
