set(headers ${headers} ../src/GpsMarker/SdkModel
)
set(currsources
  ../src/GpsMarker/SdkModel/CMakeLists.txt
  ../src/GpsMarker/SdkModel/GpsMarkerController.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerController.h
  ../src/GpsMarker/SdkModel/GpsMarkerModel.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerModel.h
  ../src/GpsMarker/SdkModel/GpsMarkerModule.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerModule.h
  ../src/GpsMarker/SdkModel/GpsMarkerView.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerView.h
  ../src/GpsMarker/SdkModel/GpsMarkerViewFactory.h
  ../src/GpsMarker/SdkModel/GpsMarkerViewFactory.cpp
  ../src/GpsMarker/SdkModel/IGpsMarkerController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\GpsMarker\\SdkModel FILES ${currsources})
