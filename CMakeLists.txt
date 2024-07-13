cmake_minimum_required(VERSION 3.16)

project(LingmoUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    #让Release也生成pdb文件
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif ()


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/.cmake/)

include(GetGitRevisionDescription)


option(LINGMOUI_BUILD_EXAMPLES "Build LingmoUI demo applications." ON)
option(LINGMOUI_BUILD_STATIC_LIB "Build static library." OFF)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Src)

#Release也支持日志打印代码位置
#target_compile_definitions(lingmouiplugin
#        PRIVATE
#        QT_MESSAGELOGCONTEXT
#)

if (LINGMOUI_BUILD_EXAMPLES)
    # add_subdirectory(example)
endif ()

message("------------------------ LingmoUI ------------------------")
message("Build LingmoUI demo applications.: ${LINGMOUI_BUILD_EXAMPLES}")
message("Build static library.: ${LINGMOUI_BUILD_STATIC_LIB}")
message("Path to LingmoUI plugin.: ${LINGMOUI_QML_PLUGIN_DIRECTORY}")

#qt_standard_project_setup(REQUIRES 6.5)
#
#qt_add_executable(appLingmoUI
#    main.cpp
#)
#
#qt_add_qml_module(appLingmoUI
#    URI LingmoUI
#    VERSION 1.0
#    QML_FILES
#        Main.qml
#)
#
## Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
## If you are developing for iOS or macOS you should consider setting an
## explicit, fixed bundle identifier manually though.
#set_target_properties(appLingmoUI PROPERTIES
##    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appLingmoUI
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)
#
#target_link_libraries(appLingmoUI
#    PRIVATE Qt6::Quick
#)
#
#include(GNUInstallDirs)
#install(TARGETS appLingmoUI
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
