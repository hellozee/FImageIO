#include <jpeg.hh>

int
main()
{
    fiio::worker::jpeg jpeg_worker("data/sample.jpg");
    jpeg_worker.save("data/jpg_copy_sample.jpg");
}
