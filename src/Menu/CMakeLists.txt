set(headers ${headers} ../src/Menu
)
set(currsources
  ../src/Menu/CMakeLists.txt
  ../src/Menu/IFunc.h
  ../src/Menu/Menu.h
  ../src/Menu/MenuDragStateChangedMessage.cpp
  ../src/Menu/MenuDragStateChangedMessage.h
  ../src/Menu/MenuSectionExpandedChangedMessage.cpp
  ../src/Menu/MenuSectionExpandedChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Menu FILES ${currsources})
include(../src/Menu/View/CMakeLists.txt)
