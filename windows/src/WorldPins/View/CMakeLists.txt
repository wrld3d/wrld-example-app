set(headers ${headers} src/WorldPins/View
)
set(currsources
  src/WorldPins/View/IWorldPinOnMapViewModule.h
  src/WorldPins/View/WorldPinOnMapCLI.cpp
  src/WorldPins/View/WorldPinOnMapCLI.h
  src/WorldPins/View/WorldPinOnMapView.cpp
  src/WorldPins/View/WorldPinOnMapView.h
  src/WorldPins/View/WorldPinOnMapViewIncludes.h
  src/WorldPins/View/WorldPinOnMapViewModule.cpp
  src/WorldPins/View/WorldPinOnMapViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa /Y-")
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\WorldPins\\View FILES ${currsources})
