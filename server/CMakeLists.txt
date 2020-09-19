project(playoff_server LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(playoff_server_library STATIC ${SOURCES})
add_library(playoff::server ALIAS playoff_server_library)

target_include_directories(playoff_server_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(playoff_server_library
    PUBLIC
        playoff::common
        spdlog::spdlog
        ${Boost_LIBRARIES}
)

add_executable(playoff_server main.cpp)
target_link_libraries(playoff_server PRIVATE playoff_server_library)
