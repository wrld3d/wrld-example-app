set(headers ${headers} src/GpsMarker
)
set(currsources
  src/GpsMarker/GpsMarker.h
  src/GpsMarker/GpsMarkerVisibilityMessage.cpp
  src/GpsMarker/GpsMarkerVisibilityMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\GpsMarker FILES ${currsources})
include(src/GpsMarker/SdkModel/CMakeLists.txt)
