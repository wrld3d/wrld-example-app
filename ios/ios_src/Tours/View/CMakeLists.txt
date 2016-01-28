if(${IOS})
set(headers ${headers} ios_src/Tours/View
)
set(currsources
  ios_src/Tours/View/CMakeLists.txt
  ios_src/Tours/View/TourDefines.h
  ios_src/Tours/View/TourDefines.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours\\View FILES ${currsources})
include(ios_src/Tours/View/TourExplorer/CMakeLists.txt)
include(ios_src/Tours/View/TourFullScreenImage/CMakeLists.txt)
include(ios_src/Tours/View/TourHovercard/CMakeLists.txt)
include(ios_src/Tours/View/TourWeb/CMakeLists.txt)
include(ios_src/Tours/View/TwitterTourExplorer/CMakeLists.txt)
endif(${IOS})
