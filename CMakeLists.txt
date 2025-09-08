cmake_minimum_required(VERSION 3.20)
project(0908_test2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 手动设置你的 Qt 路径
set(QT_PREFIX_DEBUG   "D:/Library/MSVC_2022/x64_Shared_MD")
set(QT_PREFIX_RELEASE "D:/Library/MSVC_2022/x64_Static_Release_MT")

if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        #message(STATUS "Configuring Debug build with shared Qt...")
        set(CMAKE_PREFIX_PATH ${QT_PREFIX_DEBUG})
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDebugDLL) # MDd
    else()
        #message(STATUS "Configuring Release build with static Qt...")
        set(CMAKE_PREFIX_PATH ${QT_PREFIX_RELEASE})
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded) # MT
        set(CMAKE_EXE_LINKER_FLAGS "-static")
    endif()
endif()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Concurrent
        REQUIRED
)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Concurrent
)

# Debug 模式下自动复制 DLL
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX d)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    endif()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()

    foreach (QT_LIB Core Gui Widgets Network Concurrent)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach()
endif()
