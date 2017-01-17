set(headers ${headers} ../src/WorldPins
)
set(currsources
  ../src/WorldPins/CMakeLists.txt
  ../src/WorldPins/WorldPinGainedFocusMessage.cpp
  ../src/WorldPins/WorldPinGainedFocusMessage.h
  ../src/WorldPins/WorldPinInFocusChangedLocationMessage.cpp
  ../src/WorldPins/WorldPinInFocusChangedLocationMessage.h
  ../src/WorldPins/WorldPinLostFocusMessage.cpp
  ../src/WorldPins/WorldPinLostFocusMessage.h
  ../src/WorldPins/WorldPins.h
  ../src/WorldPins/WorldPinsSelectedFocussedMessage.cpp
  ../src/WorldPins/WorldPinsSelectedFocussedMessage.h
  ../src/WorldPins/WorldPinsVisibilityMessage.cpp
  ../src/WorldPins/WorldPinsVisibilityMessage.h
  ../src/WorldPins/WorldPinHiddenStateChangedMessage.cpp
  ../src/WorldPins/WorldPinHiddenStateChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WorldPins FILES ${currsources})
include(../src/WorldPins/SdkModel/CMakeLists.txt)
