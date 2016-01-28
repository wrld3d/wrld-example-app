set(headers ${headers} ../src/Tours/SdkModel
)
set(currsources
  ../src/Tours/SdkModel/ActiveTourQuitSelectedMessageHandler.cpp
  ../src/Tours/SdkModel/ActiveTourQuitSelectedMessageHandler.h
  ../src/Tours/SdkModel/CMakeLists.txt
  ../src/Tours/SdkModel/ITourRepository.h
  ../src/Tours/SdkModel/ITourService.h
  ../src/Tours/SdkModel/TourActiveStateChangedMessageHandler.cpp
  ../src/Tours/SdkModel/TourActiveStateChangedMessageHandler.h
  ../src/Tours/SdkModel/TourAddedObserver.cpp
  ../src/Tours/SdkModel/TourAddedObserver.h
  ../src/Tours/SdkModel/TourChangeRequestMessageHandler.cpp
  ../src/Tours/SdkModel/TourChangeRequestMessageHandler.h
  ../src/Tours/SdkModel/TourModel.cpp
  ../src/Tours/SdkModel/TourModel.h
  ../src/Tours/SdkModel/TourRemovedObserver.cpp
  ../src/Tours/SdkModel/TourRemovedObserver.h
  ../src/Tours/SdkModel/TourRepository.cpp
  ../src/Tours/SdkModel/TourRepository.h
  ../src/Tours/SdkModel/TourService.cpp
  ../src/Tours/SdkModel/TourService.h
  ../src/Tours/SdkModel/TourStateModel.cpp
  ../src/Tours/SdkModel/TourStateModel.h
  ../src/Tours/SdkModel/TourWorldPinSelectionHandler.cpp
  ../src/Tours/SdkModel/TourWorldPinSelectionHandler.h
  ../src/Tours/SdkModel/TourWorldPinSelectionHandlerFactory.cpp
  ../src/Tours/SdkModel/TourWorldPinSelectionHandlerFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\SdkModel FILES ${currsources})
include(../src/Tours/SdkModel/Camera/CMakeLists.txt)
include(../src/Tours/SdkModel/States/CMakeLists.txt)
include(../src/Tours/SdkModel/TourInstances/CMakeLists.txt)
