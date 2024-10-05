cmake_minimum_required(VERSION 3.29)
project(AsteroidProj)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG        e39880d21043c46e484607a0a3fb19e291b2270d

)

FetchContent_MakeAvailable(threepp)

add_executable(AsteroidProj main.cpp)

target_link_libraries(AsteroidProj PRIVATE threepp)
