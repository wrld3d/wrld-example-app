if(${IOS})
set(headers ${headers} ios_src/Tours/View/TourWeb
)
set(currsources
  ios_src/Tours/View/TourWeb/CMakeLists.txt
  ios_src/Tours/View/TourWeb/ITourWebViewModule.h
  ios_src/Tours/View/TourWeb/TourWebView.h
  ios_src/Tours/View/TourWeb/TourWebView.mm
  ios_src/Tours/View/TourWeb/TourWebViewIncludes.h
  ios_src/Tours/View/TourWeb/TourWebViewModule.h
  ios_src/Tours/View/TourWeb/TourWebViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours\\View\\TourWeb FILES ${currsources})
endif(${IOS})
