set(headers ${headers} ../src/DirectionResultSection/SdkModel
)
set(currsources
  ../src/DirectionResultSection/SdkModel/CMakeLists.txt
  ../src/DirectionResultSection/SdkModel/DirectionsResultSectionModule.cpp
  ../src/DirectionResultSection/SdkModel/DirectionsResultSectionModule.h
  ../src/DirectionResultSection/SdkModel/IDirectionsResultSectionModule.h
  ../src/DirectionResultSection/SdkModel/DirectionResultSectionWayPointSelectedMessageHandler.cpp
  ../src/DirectionResultSection/SdkModel/DirectionResultSectionWayPointSelectedMessageHandler.h
  ../src/DirectionResultSection/SdkModel/DirectionsMenuOptionsModel.h
  ../src/DirectionResultSection/SdkModel/DirectionsMenuOptionsModel.cpp
  ../src/DirectionResultSection/SdkModel/DirectionsMenuJsonSerializer.h
  ../src/DirectionResultSection/SdkModel/DirectionsMenuItemModel.h
  ../src/DirectionResultSection/SdkModel/DirectionsMenuItemModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionResultSection\\SdkModel FILES ${currsources})