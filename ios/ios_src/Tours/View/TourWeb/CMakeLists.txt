if(${IOS})
set(headers ${headers} ios/ios_src/Tours/View/TourWeb
)
set(currsources
  ios/ios_src/Tours/View/TourWeb/ITourWebViewModule.h
  ios/ios_src/Tours/View/TourWeb/TourWebView.h
  ios/ios_src/Tours/View/TourWeb/TourWebView.mm
  ios/ios_src/Tours/View/TourWeb/TourWebViewIncludes.h
  ios/ios_src/Tours/View/TourWeb/TourWebViewModule.h
  ios/ios_src/Tours/View/TourWeb/TourWebViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours\\View\\TourWeb FILES ${currsources})
endif(${IOS})
