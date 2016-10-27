set(headers ${headers} ../src/Direction/SdkModel
)
set(currsources
  ../src/Direction/SdkModel/CMakeLists.txt
  ../src/Direction/SdkModel/FindDirectionQueryPerformer.cpp
  ../src/Direction/SdkModel/FindDirectionQueryPerformer.h
  ../src/Direction/SdkModel/FindDirectionService.cpp
  ../src/Direction/SdkModel/FindDirectionService.h
  ../src/Direction/SdkModel/FindDirectionQuery.cpp
  ../src/Direction/SdkModel/FindDirectionQuery.h
  ../src/Direction/SdkModel/FindDirectionHttpRequestFactory.cpp
  ../src/Direction/SdkModel/FindDirectionHttpRequestFactory.h
  ../src/Direction/SdkModel/FindDirectionHttpRequest.cpp
  ../src/Direction/SdkModel/FindDirectionHttpRequest.h
  ../src/Direction/SdkModel/FindDirectionResultJsonParser.cpp
  ../src/Direction/SdkModel/FindDirectionResultJsonParser.h
  ../src/Direction/SdkModel/DirectionResultModel.cpp
  ../src/Direction/SdkModel/DirectionResultModel.h
  ../src/Direction/SdkModel/DirectionRouteModel.cpp
  ../src/Direction/SdkModel/DirectionRouteModel.h
  ../src/Direction/SdkModel/DirectionInnerRouteModel.cpp
  ../src/Direction/SdkModel/DirectionInnerRouteModel.h
  ../src/Direction/SdkModel/DirectionRouteGeometryModel.cpp
  ../src/Direction/SdkModel/DirectionRouteGeometryModel.h
  ../src/Direction/SdkModel/FindDirectionServiceModule.cpp
  ../src/Direction/SdkModel/FindDirectionServiceModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Direction\\SdkModel FILES ${currsources})