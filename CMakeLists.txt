cmake_minimum_required(VERSION 3.23)

project(edgas)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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
)

enable_testing()

add_executable(
  edgas_test
  test/edgas_test.cxx
)

target_link_libraries(edgas PUBLIC yaml-cpp::yaml-cpp)

target_link_libraries(
  edgas_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(edgas_test)

# EOF