# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\chip_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chip_autogen.dir\\ParseCache.txt"
  "chip_autogen"
  )
endif()
