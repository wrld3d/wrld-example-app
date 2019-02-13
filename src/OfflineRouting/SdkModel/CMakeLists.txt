set(headers ${headers} ../src/OfflineRouting/SdkModel
)
set(currsources
  ../src/OfflineRouting/SdkModel/CMakeLists.txt
  ../src/OfflineRouting/SdkModel/IOfflineRoutingModule.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingModule.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel FILES ${currsources})
