project(playoff_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(playoff_test ${SOURCES})

target_link_libraries(playoff_test
    PUBLIC
        playoff::common
        playoff::client
        playoff::server
        GTest::gtest GTest::gmock
)

gtest_add_tests(TARGET playoff_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
