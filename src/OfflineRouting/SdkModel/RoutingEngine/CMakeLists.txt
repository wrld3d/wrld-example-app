set(headers ${headers} ../src/OfflineRouting/SdkModel/RoutingEngine
)
set(currsources
  ../src/OfflineRouting/SdkModel/RoutingEngine/CMakeLists.txt
  ../src/OfflineRouting/SdkModel/RoutingEngine/IOfflineRoutingDataBuilder.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/IOfflineRoutingDataRepository.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/IOfflineRoutingDataSearchService.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/IOfflineRoutingEngine.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingDataBuilder.cpp
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingDataBuilder.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingDataRepository.cpp
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingDataRepository.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingDataSearchService.cpp
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingDataSearchService.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingEngine.cpp
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingEngine.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingFeature.h
  ../src/OfflineRouting/SdkModel/RoutingEngine/OfflineRoutingGraphNode.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel\\RoutingEngine FILES ${currsources})