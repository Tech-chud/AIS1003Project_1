include_directories(${CMAKE_SOURCE_DIR}/Headers)

add_subdirectory(Collision)
add_subdirectory(GameSystem)
add_subdirectory(KeyListeners)
add_subdirectory(Sprites)
add_subdirectory(Util)

target_sources(AsteroidLib PRIVATE
        Collision/BaseCollisionDetector.cpp
        Collision/InelasticCollision.cpp
        Collision/ElasticCollision.cpp
        GameSystem/GameInit.cpp
        GameSystem/GameHUD.cpp
        KeyListeners/InputListener.cpp
        Sprites/Asteroid.cpp
        Sprites/Player.cpp
        Sprites/Bullet.cpp
        Util/MovingObjects.cpp
        Util/RandomGen.cpp
)

target_link_libraries(AsteroidLib PRIVATE threepp::threepp)
