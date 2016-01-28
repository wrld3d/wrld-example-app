set(headers ${headers} ../src/FlattenButton
)
set(currsources
  ../src/FlattenButton/CMakeLists.txt
  ../src/FlattenButton/FlattenButton.h
  ../src/FlattenButton/FlattenButtonModelStateChangedMessage.cpp
  ../src/FlattenButton/FlattenButtonModelStateChangedMessage.h
  ../src/FlattenButton/FlattenButtonViewStateChangedMessage.cpp
  ../src/FlattenButton/FlattenButtonViewStateChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\FlattenButton FILES ${currsources})
include(../src/FlattenButton/SdkModel/CMakeLists.txt)
include(../src/FlattenButton/View/CMakeLists.txt)
