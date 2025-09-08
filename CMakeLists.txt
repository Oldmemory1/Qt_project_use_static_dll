cmake_minimum_required(VERSION 4.0)
project(0908_test2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
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
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_PREFIX_PATH "D:/Library/MSVC_2022/x64_Shared_MD")
        find_package(Qt6 COMPONENTS
                Core
                Gui
                Widgets
                Network
                Concurrent
                REQUIRED)
        #set(CMAKE_EXE_LINKER_FLAGS "-static")
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
        if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
            set(DEBUG_SUFFIX)
            if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
                set(DEBUG_SUFFIX "d")
            endif ()
            set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
                if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                    set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
                endif ()
            endif ()
            if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
            endif ()
            foreach (QT_LIB Core Gui Widgets Network Concurrent)
                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                        "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
            endforeach (QT_LIB)
        endif ()
    endif()
endif()

