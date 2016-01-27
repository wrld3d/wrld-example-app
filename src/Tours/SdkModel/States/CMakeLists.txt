set(headers ${headers} src/Tours/SdkModel/States
)
set(currsources
  src/Tours/SdkModel/States/ITourStateMachine.h
  src/Tours/SdkModel/States/ITourStateMachineState.h
  src/Tours/SdkModel/States/TourStateMachine.cpp
  src/Tours/SdkModel/States/TourStateMachine.h
)
set(sources ${sources} ${currsources})
source_group(\\Tours\\SdkModel\\States FILES ${currsources})
