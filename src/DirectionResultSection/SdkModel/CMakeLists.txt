set(headers ${headers} ../src/DirectionResultSection/SdkModel
)
set(currsources
  ../src/DirectionResultSection/SdkModel/CMakeLists.txt
  ../src/DirectionResultSection/SdkModel/DirectionsResultSectionModule.cpp
  ../src/DirectionResultSection/SdkModel/DirectionsResultSectionModule.h
  ../src/DirectionResultSection/SdkModel/IDirectionsResultSectionModule.h
  ../src/DirectionResultSection/SdkModel/DirectionResultSectionWayPointSelectedMessageHandler.cpp
  ../src/DirectionResultSection/SdkModel/DirectionResultSectionWayPointSelectedMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionResultSection\\SdkModel FILES ${currsources})