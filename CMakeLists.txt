cmake_minimum_required(VERSION 3.5.0)
project(cubeProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(cubeProject 
    main.cpp 
    src/FFT.cpp
    src/MusicContainer.cpp
    src/Split.cpp
    src/Mode2D.cpp
    src/Mode3D.cpp
)

include_directories(include)
add_subdirectory(include/extern/raylib)
target_link_libraries(cubeProject raylib)

set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
