set(headers ${headers} ../src/Tours/TourFullScreenImage
)
set(currsources
  ../src/Tours/TourFullScreenImage/CMakeLists.txt
  ../src/Tours/TourFullScreenImage/TourFullScreenImageCeremonyBeganMessage.cpp
  ../src/Tours/TourFullScreenImage/TourFullScreenImageCeremonyBeganMessage.h
  ../src/Tours/TourFullScreenImage/TourFullScreenImageCeremonyEndedMessage.cpp
  ../src/Tours/TourFullScreenImage/TourFullScreenImageCeremonyEndedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\TourFullScreenImage FILES ${currsources})
