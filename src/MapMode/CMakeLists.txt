set(headers ${headers} src/MapMode
)
set(currsources
  src/MapMode/MapMode.h
)
set(sources ${sources} ${currsources})
source_group(\\MapMode FILES ${currsources})
include(src/MapMode/SdkModel/CMakeLists.txt)
