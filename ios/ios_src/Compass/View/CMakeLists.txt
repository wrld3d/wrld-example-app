if(${IOS})
set(headers ${headers} ios/ios_src/Compass/View
)
set(currsources
  ios/ios_src/Compass/View/CompassView.h
  ios/ios_src/Compass/View/CompassView.mm
  ios/ios_src/Compass/View/CompassViewIncludes.h
  ios/ios_src/Compass/View/CompassViewInterop.h
  ios/ios_src/Compass/View/CompassViewInterop.mm
  ios/ios_src/Compass/View/CompassViewModule.h
  ios/ios_src/Compass/View/CompassViewModule.mm
  ios/ios_src/Compass/View/ICompassViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Compass\\View FILES ${currsources})
endif(${IOS})
