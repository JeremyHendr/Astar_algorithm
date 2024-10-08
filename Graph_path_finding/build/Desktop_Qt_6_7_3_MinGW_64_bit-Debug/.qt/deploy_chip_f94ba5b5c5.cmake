include(D:/Application/QT/Examples/Qt-6.7.3/widgets/graphicsview/chip/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/chip-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_ALL_MODULES_FOUND_VIA_FIND_PACKAGE "ZlibPrivate;EntryPointPrivate;Core;Gui;Widgets;PrintSupport")

qt6_deploy_runtime_dependencies(
    EXECUTABLE D:/Application/QT/Examples/Qt-6.7.3/widgets/graphicsview/chip/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/chip.exe
    GENERATE_QT_CONF
)
