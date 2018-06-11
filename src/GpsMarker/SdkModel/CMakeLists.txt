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
  ../src/GpsMarker/SdkModel/IGpsMarkerController.h
  ../src/GpsMarker/SdkModel/IGpsMarkerModule.h
  ../src/GpsMarker/SdkModel/AccuracyRingView.h
  ../src/GpsMarker/SdkModel/AccuracyRingView.cpp
  ../src/GpsMarker/SdkModel/AccuracyRingRenderable.h
  ../src/GpsMarker/SdkModel/AccuracyRingRenderable.cpp
  ../src/GpsMarker/SdkModel/AccuracyRingRenderableFactory.h
  ../src/GpsMarker/SdkModel/AccuracyRingRenderableFactory.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\GpsMarker\\SdkModel FILES ${currsources})
