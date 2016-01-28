set(headers ${headers} ../src/GpsMarker
)
set(currsources
  ../src/GpsMarker/CMakeLists.txt
  ../src/GpsMarker/GpsMarker.h
  ../src/GpsMarker/GpsMarkerVisibilityMessage.cpp
  ../src/GpsMarker/GpsMarkerVisibilityMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\GpsMarker FILES ${currsources})
include(../src/GpsMarker/SdkModel/CMakeLists.txt)
