cmake_minimum_required(VERSION 3.29)
project(AsteroidProj)
set(CMAKE_CXX_STANDARD 20)

# Option to toggle building tests
option(ASTEROIDPROJ_BUILD_TESTS "Build tests" ON)

include_directories(${PROJECT_SOURCE_DIR}/Headers)

include(FetchContent)

FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG e39880d21043c46e484607a0a3fb19e291b2270d
)

FetchContent_MakeAvailable(threepp)

add_library(AsteroidLib)
target_sources(AsteroidLib PRIVATE src/main.cpp)
target_include_directories(AsteroidLib PRIVATE ${CMAKE_SOURCE_DIR}/Headers)
target_link_libraries(AsteroidLib PRIVATE threepp::threepp)

add_executable(AsteroidProj src/main.cpp)
target_link_libraries(AsteroidProj PRIVATE threepp::threepp)

add_subdirectory(src)


if (ASTEROIDPROJ_BUILD_TESTS)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.7.0
    )
    FetchContent_MakeAvailable(Catch2)


    enable_testing()
    add_subdirectory(tests)
endif()
