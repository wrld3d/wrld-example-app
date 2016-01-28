set(headers ${headers} ../src/VisualMap
)
set(currsources
  ../src/VisualMap/CMakeLists.txt
  ../src/VisualMap/VisualMap.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\VisualMap FILES ${currsources})
include(../src/VisualMap/SdkModel/CMakeLists.txt)
