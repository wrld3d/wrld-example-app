set(headers ${headers} ../src/MapMode
)
set(currsources
  ../src/MapMode/CMakeLists.txt
  ../src/MapMode/MapMode.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MapMode FILES ${currsources})
include(../src/MapMode/SdkModel/CMakeLists.txt)
