#pragma once

#include <string>
#include <jpeglib.h>
#include <memory>
#include <vector>

namespace fiio::jpeg{
    class worker{
        public:
            explicit worker(const std::string &filename);
            worker(const worker& rhs);

            void save(const std::string &filename, int quality=90);

            inline size_t width() { return _width; }
            inline size_t height() { return _height; }
            inline size_t pixel_size() { return _pixel_size; }
            inline int colorspace() { return _colorspace; }

        private:
            int _colorspace;
            size_t _width, _height, _pixel_size;
            std::shared_ptr<::jpeg_error_mgr> _error_manager;
            std::vector<std::vector<uint8_t>> _pixels;
    };
}
