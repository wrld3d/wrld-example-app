set(headers ${headers} ../src/DirectionsService/SdkModel
)
set(currsources
  ../src/DirectionsService/SdkModel/CMakeLists.txt
  ../src/DirectionsService/SdkModel/FindDirectionQueryPerformer.cpp
  ../src/DirectionsService/SdkModel/FindDirectionQueryPerformer.h
  ../src/DirectionsService/SdkModel/FindDirectionService.cpp
  ../src/DirectionsService/SdkModel/FindDirectionService.h
  ../src/DirectionsService/SdkModel/FindDirectionQuery.cpp
  ../src/DirectionsService/SdkModel/FindDirectionQuery.h
  ../src/DirectionsService/SdkModel/FindDirectionHttpRequestFactory.cpp
  ../src/DirectionsService/SdkModel/FindDirectionHttpRequestFactory.h
  ../src/DirectionsService/SdkModel/FindDirectionHttpRequest.cpp
  ../src/DirectionsService/SdkModel/FindDirectionHttpRequest.h
  ../src/DirectionsService/SdkModel/FindDirectionResultJsonParser.cpp
  ../src/DirectionsService/SdkModel/FindDirectionResultJsonParser.h
  ../src/DirectionsService/SdkModel/DirectionResultModel.cpp
  ../src/DirectionsService/SdkModel/DirectionResultModel.h
  ../src/DirectionsService/SdkModel/DirectionRouteModel.cpp
  ../src/DirectionsService/SdkModel/DirectionRouteModel.h
  ../src/DirectionsService/SdkModel/DirectionInnerRouteModel.cpp
  ../src/DirectionsService/SdkModel/DirectionInnerRouteModel.h
  ../src/DirectionsService/SdkModel/DirectionRouteGeometryModel.cpp
  ../src/DirectionsService/SdkModel/DirectionRouteGeometryModel.h
  ../src/DirectionsService/SdkModel/FindDirectionServiceModule.cpp
  ../src/DirectionsService/SdkModel/FindDirectionServiceModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsService\\SdkModel FILES ${currsources})