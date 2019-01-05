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
       _image_data = std::make_shared<fiio::jpeg::worker>(fname); 
    }
}

void
fiio::image::save(std::string fname, fiio::config::base config)
{

}
