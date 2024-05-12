cmake_minimum_required(VERSION 3.12)

project(Sort)

enable_testing() 

add_subdirectory(googletest)

include_directories(googletest/include)

add_executable(${PROJECT_NAME} tests/tests.cpp)

# link google test to this executable
target_link_libraries(${PROJECT_NAME} PRIVATE gtest) 

include(GoogleTest)
# discovers tests by asking the compiled test executable to enumerate its tests
gtest_discover_tests(${PROJECT_NAME}) 