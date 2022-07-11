cmake_minimum_required(VERSION 3.23)

project(2048FromScratch)

add_subdirectory(gfs)

# add_library(gfs gfs/matrix.cpp gfs/matrix.hpp gfs/logger.hpp gfs/console_logger.hpp gfs/window.hpp gfs/window.cpp)

# set_property(TARGET gfs PROPERTY CXX_STANDARD 20)

# target_include_directories(gfs PUBLIC gfs)

add_subdirectory(game2048)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    
    add_executable(2048SF 
        linux/main.cpp 
        linux/src/sdl_win.hpp 
        linux/src/sdl_wrap.hpp
        linux/src/sdl_gl.hpp
        )

    find_package(SDL2 REQUIRED)
    add_compile_options(-Wall -g  )
    set_property(TARGET 2048SF PROPERTY CXX_STANDARD 20)
    
    target_link_libraries(2048SF gfs game2048 GL ${SDL2_LIBRARIES} )
    include_directories(${SDL2_INCLUDE_DIRS})

endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(2048SF MACOSX_BUNDLE macos/AppDelegate.h macos/AppDelegate.mm macos/main.mm macos/MyViewController.h macos/MyViewController.mm macos/Base.lproj/MainMenu.xib macos/Renderer.mm macos/Renderer.h macos/MacWindow.h macos/MacWindow.mm)
    target_compile_options(2048SF PUBLIC "-fobjc-arc")
    target_link_libraries(2048SF "-framework MetalKit" "-framework Metal" "-framework QuartzCore -framework Cocoa")

    set_property(TARGET 2048SF PROPERTY CXX_STANDARD 20)

    set_property(TARGET 2048SF PROPERTY OBJC_STANDARD 11)

    set_property(TARGET 2048SF PROPERTY OBJCXX_STANDARD 20)

    target_link_libraries(2048SF gfs game2048)

    set(RESOURCE_FILES "macos/Base.lproj/MainMenu.xib")

    set_target_properties(2048SF PROPERTIES
        BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.macapp
        MACOSX_BUNDLE_BUNDLE_NAME macapp
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
        RESOURCE "${RESOURCE_FILES}"
    )


endif()
