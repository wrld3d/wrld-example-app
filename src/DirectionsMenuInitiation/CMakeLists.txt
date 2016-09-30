set(headers ${headers} ../src/DirectionsMenuInitiation
)
set(currsources
  ../src/DirectionsMenuInitiation/CMakeLists.txt
  ../src/DirectionsMenuInitiation/DirectionsMenuInitiation.h
  ../src/DirectionsMenuInitiation/DirectionsMenuStateChangedMessage.cpp  ../src/DirectionsMenuInitiation/DirectionsMenuStateChangedMessage.h
  ../src/DirectionsMenuInitiation/DirectionsMenuStage.h
  ../src/DirectionsMenuInitiation/DirectionsMenuItemHighlightMessage.h
  ../src/DirectionsMenuInitiation/DirectionsMenuItemHighlightMessage.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsMenuInitiation FILES ${currsources})
include(../src/DirectionsMenuInitiation/View/CMakeLists.txt)
include(../src/DirectionsMenuInitiation/SdkModel/CMakeLists.txt)