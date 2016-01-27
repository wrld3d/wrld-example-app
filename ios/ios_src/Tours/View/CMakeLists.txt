if(${IOS})
set(headers ${headers} ios/ios_src/Tours/View
)
set(currsources
  ios/ios_src/Tours/View/TourDefines.h
  ios/ios_src/Tours/View/TourDefines.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours\\View FILES ${currsources})
include(ios/ios_src/Tours/View/TourExplorer/CMakeLists.txt)
include(ios/ios_src/Tours/View/TourFullScreenImage/CMakeLists.txt)
include(ios/ios_src/Tours/View/TourHovercard/CMakeLists.txt)
include(ios/ios_src/Tours/View/TourWeb/CMakeLists.txt)
include(ios/ios_src/Tours/View/TwitterTourExplorer/CMakeLists.txt)
endif(${IOS})
