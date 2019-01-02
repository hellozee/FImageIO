add_subdirectory(worker)
include_directories(${WORKER_INCLUDE_DIRECTORY})

set(FIIO_SOURCES
    FImageIO.cc)

add_library( FImageIO STATIC ${FIIO_SOURCES} )
add_library( FImageIOStatic SHARED ${FIIO_SOURCES} )
target_link_libraries(
    FImageIO
    FImageIO_worker
)
