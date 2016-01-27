set(headers ${headers} src/Tours/View
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\Tours\\View FILES ${currsources})
include(src/Tours/View/TourExplorer/CMakeLists.txt)
include(src/Tours/View/TourFullScreenImage/CMakeLists.txt)
