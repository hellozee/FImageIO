#include <FImageIO/config/jpeg.hh>

fiio::config::jpeg::jpeg():
    fiio::config::base(fiio::image_format::jpeg)
{
}

fiio::config::jpeg::jpeg(std::string fname):
    fiio::config::base(fiio::image_format::jpeg)
{

}

void
fiio::config::jpeg::set_quality(int value)
{
    _quality = value;
}

void 
fiio::config::jpeg::save(std::string fname)
{
    // TODO serialization
}

void 
fiio::config::jpeg::load(std::string fname)
{
    // TODO deserialization
}
