set(headers ${headers} ../src/DirectionsMenu
)
set(currsources
  ../src/DirectionsMenu/CMakeLists.txt
  ../src/DirectionsMenu/DirectionsMenu.h
  ../src/DirectionsMenu/DirectionMenuFindDirectionMessage.cpp
  ../src/DirectionsMenu/DirectionMenuFindDirectionMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsMenu FILES ${currsources})
include(../src/DirectionsMenu/View/CMakeLists.txt)
include(../src/DirectionsMenu/SdkModel/CMakeLists.txt)