cmake_minimum_required(VERSION 3.27)
project(Steganografia)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)

add_executable(Steganografia main.cpp
        Errors.cpp
        help.cpp
        info.cpp
        check.cpp
        Engine.cpp
        BitTool.cpp

)

target_link_libraries(Steganografia sfml-graphics fmt)