cmake_minimum_required(VERSION 3.23)

project(edgas)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically define math constants (like M_PI, M_E, etc.)
if (MSVC)
    add_compile_definitions(_USE_MATH_DEFINES)
endif()


include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY  https://github.com/google/googletest.git
  GIT_TAG         v1.17.0
)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY  https://github.com/jbeder/yaml-cpp.git
  GIT_TAG         yaml-cpp-0.9.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(yaml-cpp)

add_executable(edgas)

target_sources(edgas
  PRIVATE
    src/main.cxx
    src/config.cxx
    src/simulator.cxx
    src/snapshot_writer.cxx
    src/collisions.cxx
)

enable_testing()

add_executable(
  edgas_test
  test/collisions_test.cxx
  src/collisions.cxx
)

target_link_libraries(edgas PUBLIC yaml-cpp::yaml-cpp)

target_compile_options(edgas PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
)

target_include_directories(edgas_test PUBLIC src)

target_link_libraries(
  edgas_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(edgas_test)

# EOF