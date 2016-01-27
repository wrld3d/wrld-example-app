set(headers ${headers} src/AppCamera
)
set(currsources
  src/AppCamera/AppCamera.h
)
set(sources ${sources} ${currsources})
source_group(\\AppCamera FILES ${currsources})
include(src/AppCamera/Helpers/CMakeLists.txt)
include(src/AppCamera/SdkModel/CMakeLists.txt)
