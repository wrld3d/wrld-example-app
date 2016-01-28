if(${IOS})
set(headers ${headers} ios_src/WorldPinOnMap/View
)
set(currsources
  ios_src/WorldPinOnMap/View/CMakeLists.txt
  ios_src/WorldPinOnMap/View/IWorldPinOnMapViewModule.h
  ios_src/WorldPinOnMap/View/WorldPinOnMapView.h
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewContainer.h
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewContainer.mm
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewIncludes.h
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewInterop.h
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewInterop.mm
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewModule.h
  ios_src/WorldPinOnMap/View/WorldPinOnMapViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\WorldPinOnMap\\View FILES ${currsources})
include(ios_src/WorldPinOnMap/View/Hovercards/CMakeLists.txt)
endif(${IOS})
