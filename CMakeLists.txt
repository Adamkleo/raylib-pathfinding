cmake_minimum_required(VERSION 3.15)
project(MyRaylibProject)

set(CMAKE_CXX_STANDARD 17)

# raylib setup
add_subdirectory(raylib)

add_executable(main main.cpp)
target_link_libraries(main raylib)

# macOS frameworks
if(APPLE)
    target_link_libraries(main
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreAudio"
        "-framework CoreVideo"
    )
endif()
