cmake_minimum_required(VERSION 3.11)

add_executable(ease-mode-test
  ease-mode-test.cpp
)

target_include_directories(ease-mode-test
PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
  ease-mode-test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ease-mode-test)
