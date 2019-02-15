set(headers ${headers} ../src/OfflineRouting/SdkModel/Webservice
)
set(currsources
  ../src/OfflineRouting/SdkModel/Webservice/CMakeLists.txt
  ../src/OfflineRouting/SdkModel/Webservice/IOfflineRoutingDataParser.h
  ../src/OfflineRouting/SdkModel/Webservice/IOfflineRoutingDataWebService.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataParser.cpp
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataParser.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataRequestResponse.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataWebService.cpp
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingDataWebService.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingFloorData.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingFloorPathData.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingIndoorVersion.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingMultiFloorData.h
  ../src/OfflineRouting/SdkModel/Webservice/OfflineRoutingVersionsRequestResponse.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel\\Webservice FILES ${currsources})