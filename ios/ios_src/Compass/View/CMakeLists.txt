if(${IOS})
set(headers ${headers} ios_src/Compass/View
)
set(currsources
  ios_src/Compass/View/CMakeLists.txt
  ios_src/Compass/View/CompassView.h
  ios_src/Compass/View/CompassView.mm
  ios_src/Compass/View/CompassViewIncludes.h
  ios_src/Compass/View/CompassViewInterop.h
  ios_src/Compass/View/CompassViewInterop.mm
  ios_src/Compass/View/CompassViewModule.h
  ios_src/Compass/View/CompassViewModule.mm
  ios_src/Compass/View/ICompassViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Compass\\View FILES ${currsources})
endif(${IOS})
