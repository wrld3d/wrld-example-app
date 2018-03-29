set(headers ${headers} ../src/NavRouting
)
set(currsources
  ../src/NavRouting/CMakeLists.txt
  ../src/NavRouting/NavRouting.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavRouting FILES ${currsources})
include(../src/NavRouting/SdkModel/CMakeLists.txt)
