set(headers ${headers} src/Compass
)
set(currsources
  src/Compass/Compass.h
  src/Compass/CompassGpsMode.h
  src/Compass/CompassHeadingUpdateMessage.cpp
  src/Compass/CompassHeadingUpdateMessage.h
  src/Compass/CompassModeChangedMessage.cpp
  src/Compass/CompassModeChangedMessage.h
  src/Compass/CompassModeUnauthorizedMessage.h
  src/Compass/CompassViewCycledMessage.cpp
  src/Compass/CompassViewCycledMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\Compass FILES ${currsources})
include(src/Compass/SdkModel/CMakeLists.txt)
include(src/Compass/View/CMakeLists.txt)
