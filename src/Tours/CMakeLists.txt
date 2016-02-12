set(headers ${headers} ../src/Tours
)
set(currsources
  ../src/Tours/ActiveTourQuitSelectedMessage.cpp
  ../src/Tours/ActiveTourQuitSelectedMessage.h
  ../src/Tours/CMakeLists.txt
  ../src/Tours/CurrentTourCardTappedMessage.cpp
  ../src/Tours/CurrentTourCardTappedMessage.h
  ../src/Tours/IToursModule.h
  ../src/Tours/TourActiveStateChangedMessage.cpp
  ../src/Tours/TourActiveStateChangedMessage.h
  ../src/Tours/TourChangeRequestMessage.cpp
  ../src/Tours/TourChangeRequestMessage.h
  ../src/Tours/TourOnMapSelectedMessage.cpp
  ../src/Tours/TourOnMapSelectedMessage.h
  ../src/Tours/Tours.h
  ../src/Tours/ToursModule.cpp
  ../src/Tours/ToursModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours FILES ${currsources})
include(../src/Tours/SdkModel/CMakeLists.txt)
include(../src/Tours/TourFullScreenImage/CMakeLists.txt)
include(../src/Tours/View/CMakeLists.txt)
