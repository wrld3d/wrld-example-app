set(headers ${headers} ../src/IndoorLocation
)
set(currsources
  ../src/IndoorLocation/IndoorLocation.h
  ../src/IndoorLocation/PlatformType.h
  ../src/IndoorLocation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\IndoorLocation FILES ${currsources})
include(../src/IndoorLocation/SdkModel/CMakeLists.txt)


