project(playoff_common LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(playoff_common STATIC ${SOURCES})
add_library(playoff::common ALIAS playoff_common)

target_include_directories(playoff_common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIR}
        ${BOOST_DI_INCLUDE_DIRS}
        ${BOOST_UUID_INCLUDE_DIRS}
)

target_compile_options(playoff_common
    PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/EHsc /MP /permissive- /W3 /utf-8>
        $<$<CXX_COMPILER_ID:GNU>:>
        $<$<CXX_COMPILER_ID:Clang>:>
)