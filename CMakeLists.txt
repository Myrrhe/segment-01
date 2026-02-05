cmake_minimum_required(VERSION 3.28)
project(CMakeSegment01 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# Vérifie le type de build
if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(EXECUTABLE_NAME release)
    add_executable(${EXECUTABLE_NAME} WIN32 ${SOURCES})
else()
    set(EXECUTABLE_NAME debug)
    add_executable(${EXECUTABLE_NAME} ${SOURCES})
endif()

# add_executable(main src/main.cpp)
# target_compile_features(main PRIVATE cxx_std_17)

target_include_directories(${EXECUTABLE_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories(${EXECUTABLE_NAME}
    SYSTEM PRIVATE "C:/Program Files (x86)/SFML/include"
)

# Répertoires de libs
target_link_directories(${EXECUTABLE_NAME}
    PUBLIC "C:/Program Files (x86)/SFML/lib"
)

include(FetchContent)
FetchContent_Declare(GAME
    GIT_REPOSITORY https://github.com/Myrrhe/segment-01.git
    # GIT_TAG 1.0.0
    GIT_TAG main
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(GAME)

# target_link_libraries(main PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

# Macros de préprocesseur
target_compile_definitions(${EXECUTABLE_NAME}
    PRIVATE SFML_STATIC
)

if (MSVC)
    add_compile_options(/W4 /permissive- /std:c++17)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Weffc++ -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wzero-as-null-pointer-constant -Wswitch-default -Wswitch-enum -Wmissing-include-dirs -Wunreachable-code -Winline -Winit-self -Wnon-virtual-dtor -pedantic -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winvalid-pch -Wmissing-braces -Wmultichar -Wpacked -Wpointer-arith -Wreturn-type -Wsequence-point -Wvariadic-macros -Wfloat-equal -Wstrict-aliasing=1 -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wnull-dereference -Wuninitialized -Wstringop-overflow=4 -Wstringop-truncation -Walloc-zero -Walloca -Wduplicated-branches -Wduplicated-cond -Wtrampolines -Wunused-macros -Wconditionally-supported -Wdate-time -Wvarargs -Wvector-operation-performance -Wopenmp-simd -Whsa -Wextra-semi -Warray-bounds=2 -Wformat-truncation=2 -Wunused-const-variable=1 -Wuseless-cast -Wold-style-cast -Wsign-promo -Wvirtual-inheritance -Wstrict-null-sentinel -Wsync-nand -Wunused-parameter -Wunused -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=malloc -Wmissing-noreturn -Wmissing-format-attribute -Wimplicit-fallthrough=5 -Wif-not-aligned -Wformat-signedness -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types -Wstack-protector -Wenum-compare -Wlong-long -Wmultiple-inheritance -Wdouble-promotion -Wsign-conversion -Wfloat-conversion -Wconversion -Wnoexcept -Wnoexcept-type -Wclass-memaccess -Wregister -Wctor-dtor-privacy -Wsynth -Wlto-type-mismatch -Wliteral-suffix -Wdelete-non-virtual-dtor -Wno-unused -Wno-missing-format-attribute -Wc++17-compat")
endif()

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
    sfml-audio-s
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    ws2_32
    # openal32
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
    freetype
    opengl32
    gdi32
    winmm
    psapi
    pthread
)

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
# target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)

# file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/assets")
# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets"
)
