if(${IOS})
set(headers ${headers} ios_src/Tours/View/TourExplorer
)
set(currsources
  ios_src/Tours/View/TourExplorer/CMakeLists.txt
  ios_src/Tours/View/TourExplorer/iCarouselTourExplorerViewController.h
  ios_src/Tours/View/TourExplorer/iCarouselTourExplorerViewController.mm
  ios_src/Tours/View/TourExplorer/ITourExplorerViewModule.h
  ios_src/Tours/View/TourExplorer/TourExplorerCardView.h
  ios_src/Tours/View/TourExplorer/TourExplorerCardView.mm
  ios_src/Tours/View/TourExplorer/TourExplorerView.h
  ios_src/Tours/View/TourExplorer/TourExplorerView.mm
  ios_src/Tours/View/TourExplorer/TourExplorerViewIncludes.h
  ios_src/Tours/View/TourExplorer/TourExplorerViewInterop.h
  ios_src/Tours/View/TourExplorer/TourExplorerViewInterop.mm
  ios_src/Tours/View/TourExplorer/TourExplorerViewModule.h
  ios_src/Tours/View/TourExplorer/TourExplorerViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours\\View\\TourExplorer FILES ${currsources})
endif(${IOS})
