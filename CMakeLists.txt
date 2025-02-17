cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(playground VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(proto-files/build-protos.cmake)

set(PROJECT_NAME_SERVER "${PROJECT_NAME}-server")
set(PROJECT_NAME_CLIENT "${PROJECT_NAME}-client")

add_executable(${PROJECT_NAME_SERVER} server/main.cpp)
target_link_libraries(${PROJECT_NAME_SERVER} PRIVATE proto-library)

add_executable(${PROJECT_NAME_CLIENT} client/main.cpp)
target_link_libraries(${PROJECT_NAME_CLIENT} PRIVATE proto-library)

