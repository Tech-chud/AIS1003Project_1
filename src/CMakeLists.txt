include_directories(${CMAKE_SOURCE_DIR}/Headers)

add_subdirectory(Collision)
add_subdirectory(GameControl)
add_subdirectory(HUD)
add_subdirectory(KeyListeners)
add_subdirectory(Sprites)
add_subdirectory(Util)

target_link_libraries(AsteroidProj PRIVATE threepp::threepp)