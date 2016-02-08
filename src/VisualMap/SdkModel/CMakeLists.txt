set(headers ${headers} ../src/VisualMap/SdkModel
)
set(currsources
  ../src/VisualMap/SdkModel/CMakeLists.txt
  ../src/VisualMap/SdkModel/IVisualMapController.h
  ../src/VisualMap/SdkModel/IVisualMapModel.h
  ../src/VisualMap/SdkModel/IVisualMapModule.h
  ../src/VisualMap/SdkModel/IVisualMapService.h
  ../src/VisualMap/SdkModel/IVisualMapStateHistory.h
  ../src/VisualMap/SdkModel/VisualMapController.cpp
  ../src/VisualMap/SdkModel/VisualMapController.h
  ../src/VisualMap/SdkModel/VisualMapModel.cpp
  ../src/VisualMap/SdkModel/VisualMapModel.h
  ../src/VisualMap/SdkModel/VisualMapModule.cpp
  ../src/VisualMap/SdkModel/VisualMapModule.h
  ../src/VisualMap/SdkModel/VisualMapService.cpp
  ../src/VisualMap/SdkModel/VisualMapService.h
  ../src/VisualMap/SdkModel/VisualMapState.h
  ../src/VisualMap/SdkModel/VisualMapStateHistory.cpp
  ../src/VisualMap/SdkModel/VisualMapStateHistory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\VisualMap\\SdkModel FILES ${currsources})
