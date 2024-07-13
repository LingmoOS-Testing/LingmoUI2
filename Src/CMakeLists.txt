cmake_minimum_required(VERSION 3.20)

if (LINGMOUI_BUILD_STATIC_LIB AND (QT_VERSION VERSION_GREATER_EQUAL "6.2"))
    project(lingmoui VERSION 1.0)
else ()
    project(lingmouiplugin VERSION 1.0)
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.cmake/)

include(GetQmlInstallDir)

#配置通用编译
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_standard_project_setup()
else ()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif ()

if (LINGMOUI_BUILD_STATIC_LIB)
    add_definitions(-DLINGMOUI_BUILD_STATIC_LIB)
endif ()

#导入Qt相关依赖包
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Quick Qml Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Widgets PrintSupport)

LFindQtInstallQml(LINGMO_QML_INSTALL_PATH)
message(STATUS "QML PATH: ${LINGMO_QML_INSTALL_PATH}")