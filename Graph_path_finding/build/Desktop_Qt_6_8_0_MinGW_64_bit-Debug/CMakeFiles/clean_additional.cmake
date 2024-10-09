# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Graph_finding_project_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Graph_finding_project_autogen.dir\\ParseCache.txt"
  "Graph_finding_project_autogen"
  )
endif()
