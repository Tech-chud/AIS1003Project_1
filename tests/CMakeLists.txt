add_executable(FunctionTests FunctionTests.cpp)

# Link against the sources directly because
# Unable to do this another way, i get errors.............
target_sources(FunctionTests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Sprites/Asteroid.cpp
        ${CMAKE_SOURCE_DIR}/src/Sprites/Bullet.cpp
        ${CMAKE_SOURCE_DIR}/src/Util/MovingObjects.cpp
        ${CMAKE_SOURCE_DIR}/src/Collision/InelasticCollision.cpp
        ${CMAKE_SOURCE_DIR}/src/Util/RandomGen.cpp
        ${CMAKE_SOURCE_DIR}/src/Collision/BaseCollisionDetector.cpp
)

target_link_libraries(FunctionTests PRIVATE threepp::threepp Catch2::Catch2WithMain)

enable_testing()
add_test(NAME FunctionTests COMMAND FunctionTests)
