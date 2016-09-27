set(headers ${headers} ../src/DirectionsMenuInitiation/View
)
set(currsources
  ../src/DirectionsMenuInitiation/View/CMakeLists.txt
  ../src/DirectionsMenuInitiation/View/DirectionsMenuInitiationController.h
  ../src/DirectionsMenuInitiation/View/DirectionsMenuInitiationController.cpp
  ../src/DirectionsMenuInitiation/View/DirectionsMenuInitiationScreenControl.h
  ../src/DirectionsMenuInitiation/View/DirectionsMenuInitiationScreenControl.cpp
  ../src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewModel.h
  ../src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewModel.cpp
  ../src/DirectionsMenuInitiation/View/IDirectionsMenuInitiationView.h
  ../src/DirectionsMenuInitiation/View/IDirectionsMenuInitiationViewModel.h

)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsMenuInitiation\\View FILES ${currsources})