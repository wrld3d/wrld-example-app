set(headers ${headers} ../src/OfflineRouting/SdkModel
)
set(currsources
  ../src/OfflineRouting/SdkModel/CMakeLists.txt
  ../src/OfflineRouting/SdkModel/IOfflineRoutingController.h
  ../src/OfflineRouting/SdkModel/IOfflineRoutingModule.h
  ../src/OfflineRouting/SdkModel/IOfflineRoutingServiceRouteDataBuilder.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingController.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingController.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingHelpers.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingHelpers.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingModule.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingModule.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingService.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingService.h
  ../src/OfflineRouting/SdkModel/OfflineRoutingServiceRouteDataBuilder.cpp
  ../src/OfflineRouting/SdkModel/OfflineRoutingServiceRouteDataBuilder.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel FILES ${currsources})
include(../src/OfflineRouting/SdkModel/RoutingEngine/CMakeLists.txt)
include(../src/OfflineRouting/SdkModel/Webservice/CMakeLists.txt)
