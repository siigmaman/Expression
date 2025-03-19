include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE UT_SOURCES "ut/*.cpp")
enable_testing()

add_executable(ut ${UT_SOURCES})
target_link_libraries(ut PRIVATE 
    GTest::gtest_main
    ${PROJECT_NAME}
)
target_include_directories(ut PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(ut DISCOVERY_MODE PRE_TEST)