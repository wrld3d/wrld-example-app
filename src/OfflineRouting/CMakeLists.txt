set(headers ${headers} ../src/OfflineRouting
)
set(currsources
  ../src/OfflineRouting/CMakeLists.txt
  ../src/OfflineRouting/OfflineRouting.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting FILES ${currsources})
include(../src/OfflineRouting/SdkModel/CMakeLists.txt)
