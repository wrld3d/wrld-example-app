set(headers ${headers} ../src/MyPinCreation
)
set(currsources
  ../src/MyPinCreation/CMakeLists.txt
  ../src/MyPinCreation/MyPinCreation.h
  ../src/MyPinCreation/MyPinCreationStage.h
  ../src/MyPinCreation/MyPinCreationStateChangedMessage.cpp
  ../src/MyPinCreation/MyPinCreationStateChangedMessage.h
  ../src/MyPinCreation/MyPinCreationViewSavePinMessage.cpp
  ../src/MyPinCreation/MyPinCreationViewSavePinMessage.h
  ../src/MyPinCreation/MyPinCreationViewStateChangedMessage.cpp
  ../src/MyPinCreation/MyPinCreationViewStateChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreation FILES ${currsources})
include(../src/MyPinCreation/PoiRing/CMakeLists.txt)
include(../src/MyPinCreation/SdkModel/CMakeLists.txt)
include(../src/MyPinCreation/View/CMakeLists.txt)
