cmake_minimum_required(VERSION 3.15)
project(MyRaylibProject)

set(CMAKE_CXX_STANDARD 17)

# Add raylib
add_subdirectory(raylib)

# Add include directory
include_directories(include)

# Explicit source files list
add_executable(main
    src/main.cpp
    src/grid.cpp
    src/obstacle.cpp
)

# Link raylib
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
