find_package(JPEG)

set(WORKER_SOURCES
    jpeg.hh jpeg.cc)

add_library(worker STATIC ${WORKER_SOURCES})
set_target_properties(worker PROPERTIES OUTPUT_NAME "FImageIO_worker")
