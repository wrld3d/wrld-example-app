if(${IOS})
set(headers ${headers} ios/ios_src/WorldPinOnMap/View
)
set(currsources
  ios/ios_src/WorldPinOnMap/View/IWorldPinOnMapViewModule.h
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapView.h
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewContainer.h
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewContainer.mm
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewIncludes.h
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewInterop.h
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewInterop.mm
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewModule.h
  ios/ios_src/WorldPinOnMap/View/WorldPinOnMapViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\WorldPinOnMap\\View FILES ${currsources})
include(ios/ios_src/WorldPinOnMap/View/Hovercards/CMakeLists.txt)
endif(${IOS})
