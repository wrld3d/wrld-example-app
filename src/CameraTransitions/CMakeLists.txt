set(headers ${headers} ../src/CameraTransitions
)
set(currsources
  ../src/CameraTransitions/CMakeLists.txt
  ../src/CameraTransitions/CameraTransitionControllerChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CameraTransitions FILES ${currsources})
include(../src/CameraTransitions/SdkModel/CMakeLists.txt)
