set(headers ${headers} ../src/MyPinCreation/PoiRing
)
set(currsources
  ../src/MyPinCreation/PoiRing/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreation\\PoiRing FILES ${currsources})
include(../src/MyPinCreation/PoiRing/SdkModel/CMakeLists.txt)
