cmake_minimum_required(VERSION 4.0)
project(0908_test2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Library/MSVC_2022/x64_Static_Release_MT")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Concurrent
        REQUIRED)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
add_executable(0908_test2 main.cpp)
set_target_properties(0908_test2 PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)
target_link_libraries(0908_test2
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Concurrent
)

