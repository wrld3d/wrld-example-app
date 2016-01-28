if(${IOS})
set(headers ${headers} ios_src/Tours/View/TourFullScreenImage
)
set(currsources
  ios_src/Tours/View/TourFullScreenImage/CMakeLists.txt
  ios_src/Tours/View/TourFullScreenImage/ITourFullScreenImageViewModule.h
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageView.h
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageView.mm
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewIncludes.h
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewInterop.h
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewInterop.mm
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewModule.h
  ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours\\View\\TourFullScreenImage FILES ${currsources})
endif(${IOS})
