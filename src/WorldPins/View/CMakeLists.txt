set(headers ${headers} ../src/WorldPins/View
)
set(currsources
  ../src/WorldPins/View/CMakeLists.txt
  ../src/WorldPins/View/IWorldPinInFocusViewModel.h
  ../src/WorldPins/View/IWorldPinOnMapView.h
  ../src/WorldPins/View/WorldPinInFocusObserver.cpp
  ../src/WorldPins/View/WorldPinInFocusObserver.h
  ../src/WorldPins/View/WorldPinInFocusScreenControl.cpp
  ../src/WorldPins/View/WorldPinInFocusScreenControl.h
  ../src/WorldPins/View/WorldPinInFocusViewModel.cpp
  ../src/WorldPins/View/WorldPinInFocusViewModel.h
  ../src/WorldPins/View/WorldPinOnMapController.cpp
  ../src/WorldPins/View/WorldPinOnMapController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WorldPins\\View FILES ${currsources})
