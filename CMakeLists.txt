cmake_minimum_required(VERSION 3.17)
project(Hasher_CSC__1_)

set(CMAKE_CXX_STANDARD 17)

#
# hash library with CRC32 and Sum32
#
add_library(hashlib
        scr/hashlib/hash.cpp
        scr/hashlib/hash.h)

set_target_properties(hashlib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

#
# app library with utility itself
#
add_library(applib
        scr/applib/app.cpp
        scr/applib/app.h)

set_target_properties(applib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

#
# project itself
#
add_executable(utility scr/main.cpp)

set_target_properties(utility PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

add_dependencies(utility hashlib applib)
target_link_libraries(utility hashlib applib)

#
# unit tests
#

# download googletest
configure_file(CMakeLists.txt.gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# prevent overriding the parent project's compiler/linker on windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# add googletest to build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_executable(hash_unittests
        scr/tests/main.cpp
        scr/tests/hash_unittests.cpp)

set_target_properties(hash_unittests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

target_include_directories(hash_unittests PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(hash_unittests hashlib)
target_link_libraries(hash_unittests hashlib gtest_main)