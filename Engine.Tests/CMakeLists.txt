add_executable(
        Engine_Tests
        Tests.cpp
)

target_link_libraries(
        Engine_Tests
        PRIVATE
        Engine
        Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(Engine_Tests)
