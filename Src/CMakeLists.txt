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

FindQtInstallQml(LINGMOUI_QML_PLUGIN_DIRECTORY)
message(STATUS "QML PATH: ${LINGMOUI_QML_PLUGIN_DIRECTORY}")

#遍历所有Cpp文件
file(GLOB_RECURSE CPP_FILES *.cpp *.cxx *.hpp *.h)
foreach (filepath ${CPP_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    # message(${filename})
    list(APPEND sources_files ${filename})
endforeach (filepath)

message(STATUS "Current Qt Version: ${QT_VERSION}")
if (QT_VERSION VERSION_GREATER_EQUAL "6.2")
    #遍历所有qml文件
    file(GLOB_RECURSE QML_PATHS *.qml qmldir)
    foreach (filepath ${QML_PATHS})
        if (${filepath} MATCHES "Qt${QT_VERSION_MAJOR}/")
            string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
            if (${filename} MATCHES "qmldir")
                list(APPEND resource_files ${filename})
            else ()
                list(APPEND qml_files ${filename})
            endif ()
        endif ()
    endforeach (filepath)

    #遍历所有资源文件
    file(GLOB_RECURSE RES_PATHS *.png *.jpg *.svg *.ico *.ttf *.webp *.js *.qm)
    foreach (filepath ${RES_PATHS})
        if (${filepath} MATCHES "Qt${QT_VERSION_MAJOR}/")
            string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
            list(APPEND resource_files ${filename})
        endif ()
    endforeach (filepath)

    #修改资源文件导出路径
    foreach (filepath IN LISTS qml_files resource_files)
        string(REPLACE "Qt${QT_VERSION_MAJOR}/imports/LingmoUI/" "" filename ${filepath})
        set_source_files_properties(${filepath} PROPERTIES QT_RESOURCE_ALIAS ${filename})
    endforeach ()
else ()
    message(FATAL_ERROR "LingmoUI requires Qt version >= 6.2!")
endif ()

if (LINGMOUI_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
else ()
    set(LIB_TYPE "SHARED")
endif ()

if (LINGMOUI_BUILD_STATIC_LIB)
    set(PLUGIN_TARGET_NAME "")
else ()
    #如果是动态库，则使用插件目标作为其自己的支持目标来定义 QML 模块，在这种情况下，模块必须在运行时动态加载，并且不能由其他目标直接链接到
    set(PLUGIN_TARGET_NAME ${PROJECT_NAME})
endif ()

#如果是Windows平台，则生成rc文件
set(LINGMOUI_VERSION_RC_PATH "")
if (WIN32)
    set(LINGMOUI_VERSION_RC_PATH ${CMAKE_CURRENT_BINARY_DIR}/version_${PROJECT_NAME}.rc)
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/.cmake/version_dll.rc.in
            ${LINGMOUI_VERSION_RC_PATH}
    )
endif ()

if (QT_VERSION VERSION_GREATER_EQUAL "6.2")
    #如果是Qt6.2版本以上，则使用qt_add_library，qt_add_qml_module函数添加资源文件
    qt_add_library(${PROJECT_NAME} ${LIB_TYPE})
    qt_add_qml_module(${PROJECT_NAME}
            PLUGIN_TARGET ${PLUGIN_TARGET_NAME}
            OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LingmoUI
            VERSION 1.0
            URI "LingmoUI"
            #修改qmltypes文件名称。默认fluentuiplugin.qmltypes，使用默认名称有时候import FluentUI 1.0会爆红，所以修改成plugins.qmltypes
            TYPEINFO "plugins.qmltypes"
            SOURCES ${sources_files} ${LingmoUI_VERSION_RC_PATH}
            QML_FILES ${qml_files}
            RESOURCES ${resource_files}
            RESOURCE_PREFIX "/qt/qml"
    )
else ()
    message(FATAL_ERROR "LingmoUI requires Qt version >= 6.2!")
endif ()

#安装
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/LingmoUI DESTINATION ${LINGMOUI_QML_PLUGIN_DIRECTORY}/LingmoUI)
message(STATUS "LingmoUI install path: ${LINGMOUI_QML_PLUGIN_DIRECTORY}/LingmoUI")
set(LINGMOUI_QML_PLUGIN_DIRECTORY ${LINGMOUI_QML_PLUGIN_DIRECTORY}/LingmoUI PARENT_SCOPE)
