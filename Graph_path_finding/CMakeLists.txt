# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(Graph_finding_project LANGUAGES CXX)

find_package(Qt6
    REQUIRED COMPONENTS Core Gui Widgets
    OPTIONAL_COMPONENTS PrintSupport
)

qt_standard_project_setup()

qt_add_executable(Graph_finding_project
    main.cpp
    view.cpp view.h
    Graph.h
    Edge.h
    Vertex.h
    Edge.cpp
    Graph.cpp
    Vertex.cpp
)

set_target_properties(Graph_finding_project PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(Graph_finding_project PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Resources:
set(images_resource_files
    "fileprint.png"
    "rotateleft.png"
    "rotateright.png"
    "zoomin.png"
    "zoomout.png"
)

qt_add_resources(Graph_finding_project "images"
    PREFIX
        "/"
    FILES
        ${images_resource_files}
)

# Resources:
set(gps_data_files
    "Data/graph_dc_area_2022-03-11.txt"
    "Data/vertex_test.txt"
    "Data/all_vertices.txt"
)

qt_add_resources(Graph_finding_project "gps_data"
    PREFIX
        "/"
    FILES
        ${gps_data_files}
)


if(TARGET Qt6::PrintSupport)
    target_link_libraries(Graph_finding_project PRIVATE Qt6::PrintSupport)
endif()

install(TARGETS Graph_finding_project
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Graph_finding_project
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
