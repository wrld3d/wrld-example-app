set(headers ${headers} ../src/PathDrawing
)
set(currsources
  ../src/PathDrawing/CMakeLists.txt
  ../src/PathDrawing/PathDrawingController.cpp
  ../src/PathDrawing/PathDrawingController.h
  ../src/PathDrawing/IPathDrawingController.h
  ../src/PathDrawing/WayPoint.h
  ../src/PathDrawing/WayPoint.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\PathDrawing FILES ${currsources})
include(../src/PathDrawing/SdkModel/CMakeLists.txt)