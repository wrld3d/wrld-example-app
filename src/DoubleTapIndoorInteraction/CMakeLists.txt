set(headers ${headers} ../src/DoubleTapIndoorInteraction
)
set(currsources
  ../src/DoubleTapIndoorInteraction/DoubleTapIndoorInteraction.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DoubleTapIndoorInteraction FILES ${currsources})
include(../src/DoubleTapIndoorInteraction/SdkModel/CMakeLists.txt)
