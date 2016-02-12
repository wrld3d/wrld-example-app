set(headers ${headers} ../src/Tours/View/TourExplorer
)
set(currsources
  ../src/Tours/View/TourExplorer/CMakeLists.txt
  ../src/Tours/View/TourExplorer/ITourExplorerCompositeViewController.h
  ../src/Tours/View/TourExplorer/ITourExplorerView.h
  ../src/Tours/View/TourExplorer/ITourExplorerViewModel.h
  ../src/Tours/View/TourExplorer/TourExplorerCompositeViewController.cpp
  ../src/Tours/View/TourExplorer/TourExplorerCompositeViewController.h
  ../src/Tours/View/TourExplorer/TourExplorerScreenControl.cpp
  ../src/Tours/View/TourExplorer/TourExplorerScreenControl.h
  ../src/Tours/View/TourExplorer/TourExplorerViewController.cpp
  ../src/Tours/View/TourExplorer/TourExplorerViewController.h
  ../src/Tours/View/TourExplorer/TourExplorerViewModel.cpp
  ../src/Tours/View/TourExplorer/TourExplorerViewModel.h
  ../src/Tours/View/TourExplorer/TourSelectedViewObserver.cpp
  ../src/Tours/View/TourExplorer/TourSelectedViewObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\View\\TourExplorer FILES ${currsources})
