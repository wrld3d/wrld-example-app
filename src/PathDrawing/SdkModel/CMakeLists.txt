set(headers ${headers} ../src/PathDrawing/SdkModel
)
set(currsources
  ../src/PathDrawing/SdkModel/CMakeLists.txt
  ../src/PathDrawing/SdkModel/IWayPointsFactory.h
  ../src/PathDrawing/SdkModel/WayPointType.h
  ../src/PathDrawing/SdkModel/WayPointsFactory.h
  ../src/PathDrawing/SdkModel/WayPointsFactory.cpp
  ../src/PathDrawing/SdkModel/WayPointsRepository.h
  ../src/PathDrawing/SdkModel/IWayPointsRepository.h
  ../src/PathDrawing/SdkModel/IPathDrawingModule.h
  ../src/PathDrawing/SdkModel/PathDrawingModule.h
  ../src/PathDrawing/SdkModel/PathDrawingModule.cpp
  ../src/PathDrawing/SdkModel/WayPointOnMapModel.h
  ../src/PathDrawing/SdkModel/WayPointOnMapModel.cpp
  ../src/PathDrawing/SdkModel/WayPointSelectionHandler.h
  ../src/PathDrawing/SdkModel/WayPointSelectionHandler.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\PathDrawing\\SdkModel FILES ${currsources})
