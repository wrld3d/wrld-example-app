set(headers ${headers} ../src/Tours/View/TourFullScreenImage
)
set(currsources
  ../src/Tours/View/TourFullScreenImage/CMakeLists.txt
  ../src/Tours/View/TourFullScreenImage/ITourFullScreenImageView.h
  ../src/Tours/View/TourFullScreenImage/ITourFullScreenImageViewModel.h
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageCeremonyBeganObserver.cpp
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageCeremonyBeganObserver.h
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageCeremonyEndedObserver.cpp
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageCeremonyEndedObserver.h
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageViewController.cpp
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageViewController.h
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageViewModel.cpp
  ../src/Tours/View/TourFullScreenImage/TourFullScreenImageViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\View\\TourFullScreenImage FILES ${currsources})
