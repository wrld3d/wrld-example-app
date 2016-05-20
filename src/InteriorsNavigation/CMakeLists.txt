set(headers ${headers} ../src/InteriorsNavigation
)
set(currsources
  ../src/InteriorsNavigation/InteriorsNavigation.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsNavigation FILES ${currsources})
include(../src/InteriorsNavigation/SdkModel/CMakeLists.txt)
