project(playoff_client LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE PLAYOFF_UI CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
file(GLOB_RECURSE PLAYOFF_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE PLAYOFF_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

qt5_wrap_ui(UIC_SOURCES ${PLAYOFF_UI})
qt5_add_resources(RCC_SOURCES resources/main.qrc)

add_library(playoff_client_library
    STATIC ${PLAYOFF_SOURCES} ${PLAYOFF_HEADERS} ${UIC_SOURCES} ${RCC_SOURCES})

add_library(playoff::client ALIAS playoff_client_library)

target_include_directories(playoff_client_library
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/app
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_compile_definitions(playoff_client_library PUBLIC ${Qt5Widgets_DEFINITIONS})

target_link_libraries(playoff_client_library
    PUBLIC
        playoff::common
        Qt5::Widgets
        Qt5::Gui
        ${Boost_LIBRARIES}
        spdlog::spdlog
)

set_target_properties(playoff_client_library PROPERTIES AUTOMOC ON)

add_executable(playoff_client main.cpp)
target_link_libraries(playoff_client PRIVATE playoff_client_library)

add_custom_command(TARGET playoff_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

if (WIN32)
add_custom_command(TARGET playoff_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/platforms/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/platforms/
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/styles/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5Core_DIR}/../../../plugins/styles/qwindowsvistastyle$<$<CONFIG:DEBUG>:"d">.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/styles/
        )
endif ()