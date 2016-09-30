set(headers ${headers} ../src/PathDrawing
)
set(currsources
  ../src/PathDrawing/CMakeLists.txt
  ../src/PathDrawing/PathDrawingController.cpp
  ../src/PathDrawing/PathDrawingController.h
  ../src/PathDrawing/IPathDrawingController.h
  ../src/PathDrawing/WayPointModel.h
  ../src/PathDrawing/WayPointModel.cpp
  ../src/PathDrawing/PathDrawingOptionsModel.h
  ../src/PathDrawing/PathDrawingOptionsModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\PathDrawing FILES ${currsources})
include(../src/PathDrawing/SdkModel/CMakeLists.txt)