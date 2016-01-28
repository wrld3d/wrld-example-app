set(headers ${headers} ../src/Tours/View
)
set(currsources
  ../src/Tours/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\View FILES ${currsources})
include(../src/Tours/View/TourExplorer/CMakeLists.txt)
include(../src/Tours/View/TourFullScreenImage/CMakeLists.txt)
