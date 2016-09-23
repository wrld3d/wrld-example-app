set(headers ${headers} ../src/GpsMarker/SdkModel
)
set(currsources
  ../src/GpsMarker/SdkModel/CMakeLists.txt
  ../src/GpsMarker/SdkModel/GpsMarkerController.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerController.h
  ../src/GpsMarker/SdkModel/GpsMarkerHiddenMaterial.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerHiddenMaterial.h
  ../src/GpsMarker/SdkModel/GpsMarkerHighlightMaterial.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerHighlightMaterial.h
  ../src/GpsMarker/SdkModel/GpsMarkerMaterial.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerMaterial.h
  ../src/GpsMarker/SdkModel/GpsMarkerStencilClearMaterial.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerStencilClearMaterial.h
  ../src/GpsMarker/SdkModel/GpsMarkerModel.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerModel.h
  ../src/GpsMarker/SdkModel/GpsMarkerModule.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerModule.h
  ../src/GpsMarker/SdkModel/GpsMarkerView.cpp
  ../src/GpsMarker/SdkModel/GpsMarkerView.h
  ../src/GpsMarker/SdkModel/IGpsMarkerController.h
  ../src/GpsMarker/SdkModel/IGpsMarkerModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\GpsMarker\\SdkModel FILES ${currsources})
