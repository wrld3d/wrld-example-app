set(headers ${headers} ../src/Compass
)
set(currsources
  ../src/Compass/CMakeLists.txt
  ../src/Compass/Compass.h
  ../src/Compass/CompassGpsMode.h
  ../src/Compass/CompassHeadingUpdateMessage.cpp
  ../src/Compass/CompassHeadingUpdateMessage.h
  ../src/Compass/CompassModeChangedMessage.cpp
  ../src/Compass/CompassModeChangedMessage.h
  ../src/Compass/CompassModeUnauthorizedMessage.h
  ../src/Compass/CompassViewCycledMessage.cpp
  ../src/Compass/CompassViewCycledMessage.h
  ../src/Compass/CompassIsRotatingStateChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Compass FILES ${currsources})
include(../src/Compass/SdkModel/CMakeLists.txt)
include(../src/Compass/View/CMakeLists.txt)
