set(headers ${headers} ../src/CameraTransitions
)
set(currsources
  ../src/CameraTransitions/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\CameraTransitions FILES ${currsources})
include(../src/CameraTransitions/SdkModel/CMakeLists.txt)
