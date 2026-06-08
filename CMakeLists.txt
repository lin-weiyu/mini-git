cmake_minimum_required(VERSION 3.16)

project(MiniGit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    mini-git

    src/main.cpp
    
    src/commands/InitCommand.cpp
    src/commands/AddCommand.cpp
    src/commands/CommitCommand.cpp

    src/core/Repository.cpp
    src/core/CommitManager.cpp
)

enable_testing()

find_package(GTest REQUIRED)

add_executable(
    repository_tests
    tests/RepositoryTest.cpp

    src/core/Repository.cpp
    src/core/CommitManager.cpp

    src/commands/AddCommand.cpp
    src/commands/CommitCommand.cpp
    src/commands/InitCommand.cpp
)

target_include_directories(
    repository_tests
    PRIVATE include
)

target_link_libraries(
    repository_tests
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(repository_tests)
