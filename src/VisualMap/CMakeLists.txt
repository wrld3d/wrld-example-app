set(headers ${headers} src/VisualMap
)
set(currsources
  src/VisualMap/VisualMap.h
)
set(sources ${sources} ${currsources})
source_group(\\VisualMap FILES ${currsources})
include(src/VisualMap/SdkModel/CMakeLists.txt)
