add_library(gfs 
    include/gfs/matrix.hpp
    include/gfs/logger.hpp
    include/gfs/console_logger.hpp
    include/gfs/window.hpp
    include/gfs/buffer.hpp
    include/gfs/graphics.hpp
    include/gfs/vertex.hpp
    include/gfs/renderer.hpp
    include/gfs/shader.hpp
    include/gfs/shader_library.hpp
    include/gfs/shader_library_builder.hpp

    src/matrix.cpp
    src/window.cpp
    src/buffer.cpp
    src/renderer.cpp
)

set_property(TARGET gfs PROPERTY CXX_STANDARD 20)

target_include_directories(gfs PUBLIC include)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

target_link_libraries(gfs "-framework Accelerate")

endif()
