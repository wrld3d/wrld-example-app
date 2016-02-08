set(headers ${headers} ../src/Tours/SdkModel/TourInstances/Example
)
set(currsources
  ../src/Tours/SdkModel/TourInstances/Example/CMakeLists.txt
  ../src/Tours/SdkModel/TourInstances/Example/ExampleCurrentTourCardTappedHandler.cpp
  ../src/Tours/SdkModel/TourInstances/Example/ExampleCurrentTourCardTappedHandler.h
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourHelpers.cpp
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourHelpers.h
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourPinSelectionHandler.cpp
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourPinSelectionHandler.h
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourState.cpp
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourState.h
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourStateMachineFactory.cpp
  ../src/Tours/SdkModel/TourInstances/Example/ExampleTourStateMachineFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\SdkModel\\TourInstances\\Example FILES ${currsources})
