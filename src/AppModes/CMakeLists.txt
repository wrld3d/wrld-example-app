set(headers ${headers} ../src/AppModes
)
set(currsources
  ../src/AppModes/AppModeChangedMessage.h
  ../src/AppModes/AppModes.h
  ../src/AppModes/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AppModes FILES ${currsources})
include(../src/AppModes/SdkModel/CMakeLists.txt)
include(../src/AppModes/States/CMakeLists.txt)
