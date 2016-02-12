if(${IOS})
set(headers ${headers} ios_src/Tours/View/TourHovercard
)
set(currsources
  ios_src/Tours/View/TourHovercard/CMakeLists.txt
  ios_src/Tours/View/TourHovercard/TourHovercardView.h
  ios_src/Tours/View/TourHovercard/TourHovercardView.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours\\View\\TourHovercard FILES ${currsources})
endif(${IOS})
