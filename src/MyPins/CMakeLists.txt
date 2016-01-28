set(headers ${headers} ../src/MyPins
)
set(currsources
  ../src/MyPins/CMakeLists.txt
  ../src/MyPins/MyPinAddedToMenuMessage.cpp
  ../src/MyPins/MyPinAddedToMenuMessage.h
  ../src/MyPins/MyPinRemovedFromMenuMessage.cpp
  ../src/MyPins/MyPinRemovedFromMenuMessage.h
  ../src/MyPins/MyPins.h
  ../src/MyPins/MyPinSelectedMessage.cpp
  ../src/MyPins/MyPinSelectedMessage.h
  ../src/MyPins/MyPinsHelpers.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPins FILES ${currsources})
include(../src/MyPins/SdkModel/CMakeLists.txt)
include(../src/MyPins/View/CMakeLists.txt)
