add_executable(FunctionTests FunctionTests.cpp)

target_link_libraries(FunctionTests PRIVATE Catch2::Catch2WithMain AsteroidLib)

enable_testing()
add_test(NAME FunctionTests COMMAND FunctionTests)
