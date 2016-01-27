set(headers ${headers} src/AppModes
)
set(currsources
  src/AppModes/AppModeChangedMessage.h
  src/AppModes/AppModes.h
)
set(sources ${sources} ${currsources})
source_group(\\AppModes FILES ${currsources})
include(src/AppModes/SdkModel/CMakeLists.txt)
include(src/AppModes/States/CMakeLists.txt)
