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
set(BOOST_INCLUDE_LIBRARIES heap)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.tar.xz
)
FetchContent_MakeAvailable(Boost)
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
    src/model.cxx
    src/simulator.cxx
    src/snapshot_writer.cxx
    src/collisions.cxx
    src/event_queue.cxx
)

enable_testing()

add_executable(
  edgas_test
  test/event_queue_test.cxx
  test/collisions_test.cxx
  test/model_test.cxx
  src/collisions.cxx
  src/event_queue.cxx
  src/model.cxx
)

target_link_libraries(edgas PRIVATE Boost::heap yaml-cpp::yaml-cpp)

target_compile_options(edgas PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
)

target_include_directories(edgas_test PUBLIC src)

target_link_libraries(
  edgas_test
  PRIVATE
  GTest::gtest_main
  Boost::heap
)

include(GoogleTest)
gtest_discover_tests(edgas_test)

# EOF