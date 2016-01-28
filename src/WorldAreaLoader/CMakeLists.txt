set(headers ${headers} ../src/WorldAreaLoader
)
set(currsources
  ../src/WorldAreaLoader/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\WorldAreaLoader FILES ${currsources})
include(../src/WorldAreaLoader/SdkModel/CMakeLists.txt)
