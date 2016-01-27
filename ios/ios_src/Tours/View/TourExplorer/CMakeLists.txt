if(${IOS})
set(headers ${headers} ios/ios_src/Tours/View/TourExplorer
)
set(currsources
  ios/ios_src/Tours/View/TourExplorer/iCarouselTourExplorerViewController.h
  ios/ios_src/Tours/View/TourExplorer/iCarouselTourExplorerViewController.mm
  ios/ios_src/Tours/View/TourExplorer/ITourExplorerViewModule.h
  ios/ios_src/Tours/View/TourExplorer/TourExplorerCardView.h
  ios/ios_src/Tours/View/TourExplorer/TourExplorerCardView.mm
  ios/ios_src/Tours/View/TourExplorer/TourExplorerView.h
  ios/ios_src/Tours/View/TourExplorer/TourExplorerView.mm
  ios/ios_src/Tours/View/TourExplorer/TourExplorerViewIncludes.h
  ios/ios_src/Tours/View/TourExplorer/TourExplorerViewInterop.h
  ios/ios_src/Tours/View/TourExplorer/TourExplorerViewInterop.mm
  ios/ios_src/Tours/View/TourExplorer/TourExplorerViewModule.h
  ios/ios_src/Tours/View/TourExplorer/TourExplorerViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours\\View\\TourExplorer FILES ${currsources})
endif(${IOS})
