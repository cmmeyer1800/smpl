cmake_minimum_required(VERSION 3.15)
project(smpl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

Include(FetchContent)

set(SMPL_TEST_DIR test)
set(SMPL_INCLUDE_DIR include)
set(SMPL_SRC_DIR src)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_library(smpl_lib ${SMPL_INCLUDE_DIR}/smpl.hpp ${SMPL_SRC_DIR}/smpl.cpp)
target_include_directories(smpl_lib PUBLIC ${SMPL_INCLUDE_DIR})

option(SMPL_BUILD_TESTS "Build tests" ON)

if(SMPL_BUILD_TESTS)
    add_executable(tests ${SMPL_TEST_DIR}/test.cpp)
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
    target_link_libraries(tests PRIVATE smpl_lib)
endif()

add_executable(smpl ${SMPL_SRC_DIR}/main.cpp)
target_link_libraries(smpl PRIVATE smpl_lib)