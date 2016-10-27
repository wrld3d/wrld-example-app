set(headers ${headers} ../src/DirectionsMenu/SdkModel
)
set(currsources
  ../src/DirectionsMenu/SdkModel/CMakeLists.txt
  ../src/DirectionsMenu/SdkModel/DirectionsMenuModule.cpp
  ../src/DirectionsMenu/SdkModel/DirectionsMenuModule.h
  ../src/DirectionsMenu/SdkModel/IDirectionsMenuModule.h
  ../src/DirectionsMenu/SdkModel/DirectionMenuFindDirectionMessageHandler.cpp
  ../src/DirectionsMenu/SdkModel/DirectionMenuFindDirectionMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsMenu\\SdkModel FILES ${currsources})