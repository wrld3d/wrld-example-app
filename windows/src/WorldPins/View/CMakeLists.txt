set(headers ${headers} src/WorldPins/View
)
set(currsources_noclr
  src/WorldPins/View/WorldPinOnMapViewIncludes.h
  src/WorldPins/View/WorldPinOnMapViewModule.cpp
  src/WorldPins/View/WorldPinOnMapViewModule.h
  src/WorldPins/View/WorldPinOnMapView.h
)
set(currsources
  src/WorldPins/View/WorldPinOnMapCLI.cpp
  src/WorldPins/View/WorldPinOnMapCLI.h
  src/WorldPins/View/WorldPinOnMapView.cpp
  src/WorldPins/View/WorldPinOnMapViewImpl.cpp
  src/WorldPins/View/WorldPinOnMapViewImpl.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\WorldPins\\View FILES ${currsources} ${currsources_noclr})
