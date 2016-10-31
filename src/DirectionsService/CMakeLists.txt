set(headers ${headers} ../src/DirectionsService
)
set(currsources
  ../src/DirectionsService/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsService FILES ${currsources})
include(../src/DirectionsService/SdkModel/CMakeLists.txt)