cmake_minimum_required(VERSION 3.12)
project(Yahtzee)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_library(gilded_rose GildedRose.cc GildedRose.h)

add_executable(unit_tests GildedRoseUnitTests.cc)
target_link_libraries(unit_tests PRIVATE gilded_rose gtest_main)
add_test(NAME unit_tests COMMAND unit_tests)

add_executable(text_tests GildedRoseTextTests.cc)
target_link_libraries(text_tests PRIVATE gilded_rose)
add_test(NAME text_tests COMMAND text_tests)
