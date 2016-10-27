set(headers ${headers} ../src/Direction
)
set(currsources
  ../src/Direction/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Direction FILES ${currsources})
include(../src/Direction/SdkModel/CMakeLists.txt)