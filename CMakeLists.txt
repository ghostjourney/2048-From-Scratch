cmake_minimum_required(VERSION 3.23)

project(2048FromScratch LANGUAGES C CXX OBJC OBJCXX)

include(FetchContent)
FetchContent_Declare(
	glfw3
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG  45ce5ddd197d5c58f50fdd3296a5131c894e5527 # version 3.3 stable
)

FetchContent_MakeAvailable(glfw3)

add_executable(2048SF src/main.mm)

set_property(TARGET 2048SF PROPERTY CXX_STANDARD 20)

set_property(TARGET 2048SF PROPERTY OBJC_STANDARD 11)

set_property(TARGET 2048SF PROPERTY OBJCXX_STANDARD 20)

target_link_libraries(2048SF glfw)

if(APPLE)
    target_compile_options(2048SF PUBLIC "-fobjc-arc")
    target_link_libraries(2048SF "-framework Metal" "-framework QuartzCore")
    set_target_properties(2048SF PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Metal")
endif()

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)






