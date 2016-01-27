set(headers ${headers} src/Compass/View
)
set(currsources
  src/Compass/View/CompassController.cpp
  src/Compass/View/CompassController.h
  src/Compass/View/CompassScreenControl.cpp
  src/Compass/View/CompassScreenControl.h
  src/Compass/View/CompassViewModel.cpp
  src/Compass/View/CompassViewModel.h
  src/Compass/View/ICompassView.h
  src/Compass/View/ICompassViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\Compass\\View FILES ${currsources})
