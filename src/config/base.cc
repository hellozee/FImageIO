#include <FImageIO/config/base.hh>

fiio::config::base::base(fiio::image_format format):
    _format(format)
{
}

fiio::config::base::base(fiio::image_format format, std::string fname):
    _format(format), _filename(fname)
{
}
