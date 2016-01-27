if(${IOS})
set(headers ${headers} ios/ios_src/Tours/View/TourHovercard
)
set(currsources
  ios/ios_src/Tours/View/TourHovercard/TourHovercardView.h
  ios/ios_src/Tours/View/TourHovercard/TourHovercardView.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours\\View\\TourHovercard FILES ${currsources})
endif(${IOS})
