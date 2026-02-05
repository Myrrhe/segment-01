cmake_minimum_required(VERSION 3.28)
project(CMakeSegment01 LANGUAGES CXX)

# Active la génération de compile_commands.json pour SonarQube
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Définit le standard C++17 et exige sa prise en charge
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Répertoire de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Récupération de tous les fichiers sources
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# Détection du type de build et nom de l'exécutable
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(EXECUTABLE_NAME release)
else()
    set(EXECUTABLE_NAME debug)
endif()

# Création de l'exécutable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Inclusion des headers
target_include_directories(${EXECUTABLE_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_include_directories(${EXECUTABLE_NAME}
    SYSTEM PRIVATE "C:/Program Files (x86)/SFML/include"
)

# Lien avec les librairies SFML statiques et dépendances système
target_link_directories(${EXECUTABLE_NAME}
    PUBLIC "C:/Program Files (x86)/SFML/lib"
)

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE SFML_STATIC)

# Options de compilation spécifiques selon le compilateur
if (MSVC)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -Weffc++ -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wzero-as-null-pointer-constant -Wswitch-default -Wswitch-enum -Wmissing-include-dirs -Wunreachable-code -Winline -Winit-self -Wnon-virtual-dtor -pedantic -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winvalid-pch -Wmissing-braces -Wmultichar -Wpacked -Wpointer-arith -Wreturn-type -Wsequence-point -Wvariadic-macros -Wfloat-equal -Wstrict-aliasing=1 -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wnull-dereference -Wuninitialized -Wstringop-overflow=4 -Wstringop-truncation -Walloc-zero -Walloca -Wduplicated-branches -Wduplicated-cond -Wtrampolines -Wunused-macros -Wconditionally-supported -Wdate-time -Wvarargs -Wvector-operation-performance -Wopenmp-simd -Whsa -Wextra-semi -Warray-bounds=2 -Wformat-truncation=2 -Wunused-const-variable=1 -Wuseless-cast -Wold-style-cast -Wsign-promo -Wvirtual-inheritance -Wstrict-null-sentinel -Wsync-nand -Wunused-parameter -Wunused -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=malloc -Wmissing-noreturn -Wmissing-format-attribute -Wimplicit-fallthrough=5 -Wif-not-aligned -Wformat-signedness -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types -Wstack-protector -Wenum-compare -Wmultiple-inheritance -Wdouble-promotion -Wsign-conversion -Wfloat-conversion -Wconversion -Wnoexcept -Wnoexcept-type -Wclass-memaccess -Wregister -Wctor-dtor-privacy -Wsynth -Wlto-type-mismatch -Wliteral-suffix -Wdelete-non-virtual-dtor -Wno-unused -Wno-missing-format-attribute -Wc++17-compat -Wno-cast-function-type)
endif()
# -Wlong-long

# Librairies SFML + dépendances Windows
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    sfml-audio-s
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    ws2_32
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

set(SRC_ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(DEST_ASSETS "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets")

# Test source
if(EXISTS "${SRC_ASSETS}" AND IS_DIRECTORY "${SRC_ASSETS}")
    set(SOURCE_EXISTS TRUE)
else()
    set(SOURCE_EXISTS FALSE)
endif()

# Test destination (note: generator expression évaluée plus tard, donc limité)
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/assets")  # Approximation
    set(DEST_EXISTS TRUE)
else()
    set(DEST_EXISTS FALSE)
endif()

if(DEST_EXISTS)
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets"
    )
endif()

if(SOURCE_EXISTS)
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets"
    )
else()
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets"
    )
endif()

# Inclure le sous-projet GAME (FetchContent)
include(FetchContent)
FetchContent_Declare(
    GAME
    GIT_REPOSITORY https://github.com/Myrrhe/segment-01.git
    GIT_TAG main
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(GAME)

# Définir le projet de démarrage dans Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXECUTABLE_NAME})
