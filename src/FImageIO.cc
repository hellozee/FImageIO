#include "worker/jpeg.hh"

#include <FImageIO/FImageIO>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

fiio::image::image(std::string fname):
    _filename(fname)
{
    fs::path p(fname); 
    auto extension = p.extension().u8string();

    if(extension.empty()){
        throw std::runtime_error("I am not sure about the format, please \
                                    give the file an extension");
    }

    if(extension == "jpg" || extension == "jpeg" || extension == "jpe" ||
            extension == "jif" || extension == "jfi" || extension == "jfif") {
       _image_data = std::make_shared<fiio::worker::jpeg>(fname); 
    }
}

void
fiio::image::save(const std::string &fname,
        std::shared_ptr<fiio::config::base> conf)
{
    switch (conf->format()){
        case fiio::image_format::jpeg:{
            // casts to fiio::config::jpeg and calls the respective function
            auto jpeg_conf = std::dynamic_pointer_cast<fiio::config::jpeg>(conf);    
            save_jpeg_config(fname, jpeg_conf);
            break;
        }

        case fiio::image_format::png:{
            // casts to fiio::config::png and calls the respective function
            break;
        }
    }
}

void 
fiio::image::save_jpeg_config(const std::string &fname,
        std::shared_ptr<fiio::config::jpeg> conf)
{
    // haven't started working on serialization
}
