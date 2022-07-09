cmake_minimum_required(VERSION 3.23)

project(2048FromScratch)

add_library(library library/matrix.cpp library/matrix.hpp library/logger.hpp library/console_logger.hpp library/window.hpp library/window.cpp)

set_property(TARGET library PROPERTY CXX_STANDARD 20)

target_include_directories(library PUBLIC library)


add_library(game game/game.cpp game/game.hpp)
set_property(TARGET game PROPERTY CXX_STANDARD 20)

target_include_directories(game PUBLIC game)

target_link_libraries(game library)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_executable(2048SF linux/main.cpp)

    set_property(TARGET 2048SF PROPERTY CXX_STANDARD 20)

    target_link_libraries(2048SF library game)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(2048SF MACOSX_BUNDLE macos/AppDelegate.h macos/AppDelegate.mm macos/main.mm macos/MyViewController.h macos/MyViewController.mm macos/Base.lproj/MainMenu.xib macos/Renderer.mm macos/Renderer.h macos/MacWindow.h macos/MacWindow.mm)
    target_compile_options(2048SF PUBLIC "-fobjc-arc")
    target_link_libraries(2048SF "-framework MetalKit" "-framework Metal" "-framework QuartzCore -framework Cocoa")

    set_property(TARGET 2048SF PROPERTY CXX_STANDARD 20)

    set_property(TARGET 2048SF PROPERTY OBJC_STANDARD 11)

    set_property(TARGET 2048SF PROPERTY OBJCXX_STANDARD 20)

    target_link_libraries(2048SF library game)

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
