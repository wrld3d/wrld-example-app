set(headers ${headers} ../src/OfflineRouting/SdkModel/Webservice
)
set(currsources
  ../src/OfflineRouting/SdkModel/Webservice/CMakeLists.txt
  ../src/OfflineRouting/SdkModel/Webservice/IOfflineRoutingDataWebService.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataWebService.cpp
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataWebService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel\\Webservice FILES ${currsources})