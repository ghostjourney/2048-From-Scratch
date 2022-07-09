add_library(game2048 
    include/game2048/game2048.hpp

    src/game2048.cpp
)

set_property(TARGET game2048 PROPERTY CXX_STANDARD 20)

target_include_directories(game2048 PUBLIC include)

target_link_libraries(game2048 gfs)
