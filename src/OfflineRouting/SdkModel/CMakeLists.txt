set(headers ${headers} ../src/OfflineRouting/SdkModel
)
set(currsources
  ../src/OfflineRouting/SdkModel/CMakeLists.txt
  ../src/OfflineRouting/SdkModel/IOfflineRoutingModule.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingModule.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingModule.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingService.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel FILES ${currsources})
include(../src/OfflineRouting/SdkModel/Webservice/CMakeLists.txt)
