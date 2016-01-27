set(headers ${headers} src/CameraTransitions
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\CameraTransitions FILES ${currsources})
include(src/CameraTransitions/SdkModel/CMakeLists.txt)
