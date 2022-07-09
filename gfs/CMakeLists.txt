add_library(gfs 
    include/gfs/matrix.hpp
    include/gfs/logger.hpp
    include/gfs/console_logger.hpp
    include/gfs/window.hpp
    include/gfs/buffer.hpp

    src/matrix.cpp
    src/window.cpp
    src/buffer.cpp
)

set_property(TARGET gfs PROPERTY CXX_STANDARD 20)

target_include_directories(gfs PUBLIC include)
