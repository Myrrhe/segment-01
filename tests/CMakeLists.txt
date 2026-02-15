include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.3
)

FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(tests
    ${TEST_SOURCES}
)

target_compile_options(tests PRIVATE -O0 -g --coverage)
target_link_options(tests PRIVATE --coverage)

target_link_libraries(tests
    PRIVATE
        segment01
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(tests)
