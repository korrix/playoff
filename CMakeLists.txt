cmake_minimum_required (VERSION 3.18)
project(playoff LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Dependencies
find_package(Boost COMPONENTS system REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Gui)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

# Header only libraries
find_path(BOOST_DI_INCLUDE_DIRS "boost/di.hpp")
find_path(BOOST_UUID_INCLUDE_DIRS "boost/uuid/uuid.hpp")

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)

option(BUILD_TESTING "Build tests" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    add_subdirectory(test)
endif()

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION bin
        COMPONENT applications)

add_subdirectory(packaging)