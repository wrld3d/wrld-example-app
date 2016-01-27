if(${IOS})
set(headers ${headers} ios/ios_src/Tours/View/TourFullScreenImage
)
set(currsources
  ios/ios_src/Tours/View/TourFullScreenImage/ITourFullScreenImageViewModule.h
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageView.h
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageView.mm
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewIncludes.h
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewInterop.h
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewInterop.mm
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewModule.h
  ios/ios_src/Tours/View/TourFullScreenImage/TourFullScreenImageViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours\\View\\TourFullScreenImage FILES ${currsources})
endif(${IOS})
