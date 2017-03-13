set(headers ${headers} ../src/AttractMode
)
set(currsources
  ../src/AttractMode/CMakeLists.txt
  ../src/AttractMode/AttractModeStateChangedMessage.cpp
  ../src/AttractMode/AttractModeStateChangedMessage.h
  ../src/AttractMode/AttractMode.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AttractMode FILES ${currsources})

include(../src/AttractMode/SdkModel/States/CMakeLists.txt)
