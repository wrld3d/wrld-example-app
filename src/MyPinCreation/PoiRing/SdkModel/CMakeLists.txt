set(headers ${headers} ../src/MyPinCreation/PoiRing/SdkModel
)
set(currsources
  ../src/MyPinCreation/PoiRing/SdkModel/CMakeLists.txt
  ../src/MyPinCreation/PoiRing/SdkModel/IPoiRingController.h
  ../src/MyPinCreation/PoiRing/SdkModel/IPoiRingModule.h
  ../src/MyPinCreation/PoiRing/SdkModel/IPoiRingTouchController.h
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingController.cpp
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingController.h
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingModule.cpp
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingModule.h
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingRenderable.cpp
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingRenderable.h
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingTouchController.cpp
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingTouchController.h
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingView.cpp
  ../src/MyPinCreation/PoiRing/SdkModel/PoiRingView.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreation\\PoiRing\\SdkModel FILES ${currsources})
