set(headers ${headers} ../src/NavRouting/SdkModel
)
set(currsources
  ../src/NavRouting/SdkModel/CMakeLists.txt
  ../src/NavRouting/SdkModel/INavRoutingServiceController.h
  ../src/NavRouting/SdkModel/NavRoutingServiceController.cpp
  ../src/NavRouting/SdkModel/NavRoutingServiceController.h
  ../src/NavRouting/SdkModel/NavRouteDrawingVertexData.cpp
  ../src/NavRouting/SdkModel/NavRouteDrawingVertexData.h
  ../src/NavRouting/SdkModel/NavRoutingDirectionModel.cpp
  ../src/NavRouting/SdkModel/NavRoutingDirectionModel.h
  ../src/NavRouting/SdkModel/NavRoutingLocationModel.cpp
  ../src/NavRouting/SdkModel/NavRoutingLocationModel.h
  ../src/NavRouting/SdkModel/NavRoutingRouteModel.cpp
  ../src/NavRouting/SdkModel/NavRoutingRouteModel.h
  ../src/NavRouting/SdkModel/NavRouteDrawingController.cpp
  ../src/NavRouting/SdkModel/NavRouteDrawingController.h
  ../src/NavRouting/SdkModel/NavRoutingModule.cpp
  ../src/NavRouting/SdkModel/NavRoutingModule.h
  ../src/NavRouting/SdkModel/NavRoutingViewPerformedRouteQueryMessageHandler.cpp
  ../src/NavRouting/SdkModel/NavRoutingViewPerformedRouteQueryMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavRouting\\SdkModel FILES ${currsources})
