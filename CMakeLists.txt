cmake_minimum_required(VERSION 3.16)
project(Fire_Fighter LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject
        "src/main.cpp"
        "src/ui.cpp"
        "src/ui.h"
        "src/settings.cpp"
        "src/settings.h"
        "src/game.cpp"
        "src/game.h"
        "src/entity.cpp"
        "src/entity.h"
        "src/player.cpp"
        "src/player.h"
        "src/enemy.cpp"
        "src/enemy.h"
        "src/bullet.cpp"
        "src/bullet.h"
        "src/bullet.cpp"
        "src/metrics.cpp"
        "src/metrics.h"
        "src/powerup.cpp"
        "src/powerup.h"
        "src/barrier.cpp"
        "src/barrier.h"
        "src/enemywave.cpp"
        "src/enemywave.h")

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-audio)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET CMakeSFMLProject
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
            VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
