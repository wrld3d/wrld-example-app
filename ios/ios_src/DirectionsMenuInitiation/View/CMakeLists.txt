if(${IOS})
set(headers ${headers} ios_src/DirectionsMenuInitiation/View
)
set(currsources
  ios_src/DirectionsMenuInitiation/View/CMakeLists.txt
  ios_src/DirectionsMenuInitiation/View/IDirectionsMenuInitiationViewModule.h
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationView.h
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationView.mm
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewIncludes.h
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewInterop.h
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewInterop.mm
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewModule.h
  ios_src/DirectionsMenuInitiation/View/DirectionsMenuInitiationViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\DirectionsMenuInitiation\\View FILES ${currsources})
endif(${IOS})
