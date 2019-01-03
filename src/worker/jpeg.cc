#include "jpeg.hh"

fiio::jpeg::worker::worker(const std::string &filename):
    fiio::base(jpeg)
{
    auto decompress_dt = [] ( ::jpeg_decompress_struct *ds){
        ::jpeg_destroy_decompress(ds);
    };

    std::unique_ptr<::jpeg_decompress_struct, decltype(decompress_dt)> cinfo( 
                                    new ::jpeg_decompress_struct, decompress_dt );

    _error_manager = std::make_shared<::jpeg_error_mgr>();

    auto file_dt = [] (FILE *file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(file_dt)> infile(
                                        fopen(filename.c_str(), "rb"), file_dt);

    if(infile.get() == NULL) {
        throw std::runtime_error("Can't find the file sorry");
    }

    cinfo->err = ::jpeg_std_error(_error_manager.get());
    _error_manager->error_exit = []( ::j_common_ptr cinfo){
        char error_message[JMSG_LENGTH_MAX];
        (*(cinfo->err->format_message))(cinfo, error_message);
        throw std::runtime_error(error_message);
    };

    ::jpeg_create_decompress(cinfo.get());
    ::jpeg_stdio_src(cinfo.get(), infile.get());
    auto temp = ::jpeg_read_header(cinfo.get(), TRUE);
    if(temp != 1){
        throw std::runtime_error("This is not JAYPEG.");
    }

    ::jpeg_start_decompress(cinfo.get());

    _width = cinfo->output_width;
    _height = cinfo->output_height;
    _pixel_size = cinfo->output_components;
    _colorspace = cinfo->out_color_space;

    size_t row_stride = _width * _pixel_size;
    _pixels.clear();
    _pixels.reserve(_height);

    while(cinfo->output_scanline < _height){
        std::vector<uint8_t> row_vector(row_stride);
        uint8_t *data = row_vector.data();
        ::jpeg_read_scanlines(cinfo.get(), &data, 1);
        _pixels.push_back(row_vector);
    }

    ::jpeg_finish_decompress(cinfo.get());
}

fiio::jpeg::worker::worker(const fiio::jpeg::worker& rhs):
    fiio::base(jpeg)
{
    _error_manager = rhs._error_manager;
    _pixels = rhs._pixels;
    _width = rhs._width;
    _height = rhs._height;
    _pixel_size = rhs._pixel_size;
    _colorspace = rhs._colorspace;
}

void
fiio::jpeg::worker::save(const std::string &filename)
{
    if(_quality < 0)
        _quality = 0;
    if(_quality > 100)
        _quality = 100;

    auto file_dt = [] (FILE *file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(file_dt)> outfile(
                                        fopen(filename.c_str(), "wb"), file_dt);

    if(outfile.get() == NULL){
        throw std::runtime_error("Could not open " + filename);
    }

    auto compress_dt = []( ::jpeg_compress_struct *cs){
        ::jpeg_destroy_compress(cs);
    };

    std::unique_ptr<::jpeg_compress_struct, decltype(compress_dt)>cinfo(
                                        new ::jpeg_compress_struct, compress_dt);

    ::jpeg_create_compress(cinfo.get());
    ::jpeg_stdio_dest(cinfo.get(), outfile.get());
    cinfo->image_width = _width;
    cinfo->image_height = _height;
    cinfo->input_components = _pixel_size;
    cinfo->in_color_space = static_cast<::J_COLOR_SPACE>(_colorspace);
    cinfo->err = ::jpeg_std_error(_error_manager.get());
    ::jpeg_set_defaults(cinfo.get());
    ::jpeg_set_quality(cinfo.get(), _quality, TRUE);
    ::jpeg_start_compress(cinfo.get(), TRUE);

    for(auto const& row_vector : _pixels){
        ::JSAMPROW buffer[1];
        buffer[0] = const_cast<::JSAMPROW>(row_vector.data());
        ::jpeg_write_scanlines(cinfo.get(), buffer, 1);
    }

    ::jpeg_finish_compress(cinfo.get());
}
