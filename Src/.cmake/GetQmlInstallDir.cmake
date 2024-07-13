# Author: Elysia
# 13/7/2024
# MIT License

include(CMakeParseArguments)

# Import necessary packages
find_package(ECM REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(ECMQueryQt)

# Return the Qml installation path using LINGMO_QML_INSTALL_PATH
function(LFindQtInstallQml LINGMO_QML_INSTALL_PATH)
    ecm_query_qt(TEMP_QML_INSTALL_PATH QT_INSTALL_QML)
    message(STATUS "QML PATH: ${TEMP_QML_INSTALL_PATH}")
    set(${LINGMO_QML_INSTALL_PATH} ${TEMP_QML_INSTALL_PATH} PARENT_SCOPE)
endfunction()
